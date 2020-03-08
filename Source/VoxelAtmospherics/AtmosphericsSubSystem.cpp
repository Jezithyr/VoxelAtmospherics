// Fill out your copyright notice in the Description page of Project Settings.


#include "AtmosphericsSubSystem.h"

void UAtmosphericsSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeChunks();
	UE_LOG(LogTemp, Warning, TEXT("test 2"));
}

void UAtmosphericsSubSystem::Deinitialize()
{
	DestroyChunks();
}

void UAtmosphericsSubSystem::CreateChunk(FIntVector ChunkCoords)
{
	FActorSpawnParameters VoxelChunkParams;
	VoxelChunkParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (Chunks.Contains(ChunkCoords)) return; //exit if there is already a chunk in the list
	AVoxelChunk* NewChunk = GetWorld()->SpawnActor<AVoxelChunk>(VoxelChunkParams);
	
	Chunks.Add(ChunkCoords, NewChunk);
}

void UAtmosphericsSubSystem::InitializeChunks()
{
	//this can be optimized but fuck it
	
	for (int x = (-ChunkExtents.Z); x < (ChunkExtents.X); ++x)
	{
		for (int y = (-ChunkExtents.Z); y < (ChunkExtents.Y); ++y)
		{
			for (int z = (-ChunkExtents.Z); z < (ChunkExtents.Z); ++z)
			{
				CreateChunk(FIntVector(x,y,z));
			}
		}
	}
}

void UAtmosphericsSubSystem::DestroyChunks()
{
	for (auto Element : Chunks)
	{
		Element.Value->Destroy();
	}

	Chunks.Empty();

}

FIntVector UAtmosphericsSubSystem::WorldToChunkPos(FVector WorldPos)
{
	FIntVector ReturnVector;

	ReturnVector.X = floor(WorldPos.X /ChunkSize);
	ReturnVector.Y = floor(WorldPos.Y / ChunkSize);
	ReturnVector.Z = floor(WorldPos.Z / ChunkSize);
	return ReturnVector;
}

FVector UAtmosphericsSubSystem::ChunkPosToWorld(FIntVector ChunkPos)
{
	FVector ReturnVector;
	ReturnVector.X = (ChunkPos.X * ChunkSize) + Origin.X;
	ReturnVector.Y = (ChunkPos.Y * ChunkSize) + Origin.Y;
	ReturnVector.Z = (ChunkPos.Z * ChunkSize) + Origin.Z;
	return ReturnVector;
}

AVoxelChunk* UAtmosphericsSubSystem::GetChunk(FIntVector ChunkCoords)
{
	return *(Chunks.Find(ChunkCoords));
}

AVoxelChunk* UAtmosphericsSubSystem::GetChunkFromPos(FVector WorldPos)
{
	return GetChunk(WorldToChunkPos(WorldPos));
}

FIntVector UAtmosphericsSubSystem::GetChunkCoords(AVoxelChunk* ChunkToFind)
{
	return *(Chunks.FindKey(ChunkToFind));
}

FVector UAtmosphericsSubSystem::GetChunkWorldPos(AVoxelChunk* ChunkToFind)
{
	return ChunkPosToWorld(GetChunkCoords(ChunkToFind));
}
