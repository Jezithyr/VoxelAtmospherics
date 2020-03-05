// Fill out your copyright notice in the Description page of Project Settings.


#include "AtmosphericsSubSystem.h"

void UAtmosphericsSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeChunks();
	
}

void UAtmosphericsSubSystem::Deinitialize()
{
	DestroyChunks();
}

void UAtmosphericsSubSystem::CreateChunk(FIntVector ChunkCoords)
{
}

void UAtmosphericsSubSystem::InitializeChunks()
{
	
}

void UAtmosphericsSubSystem::DestroyChunks()
{
	
}

AVoxelChunk* UAtmosphericsSubSystem::GetChunk(FIntVector ChunkCoords)
{
	return Chunks.Find(ChunkCoords);
}

AVoxelChunk* UAtmosphericsSubSystem::GetChunkFromPos(FVector WorldPos)
{
	
}

FIntVector UAtmosphericsSubSystem::GetChunkCoords(AVoxelChunk* ChunkToFind)
{
	return *(Chunks.FindKey(*ChunkToFind));
}

FVector UAtmosphericsSubSystem::GetChunkWorldPos(AVoxelChunk* ChunkToFind)
{
	
}
