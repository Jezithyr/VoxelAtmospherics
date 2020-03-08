// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VoxelChunk.h"
#include "Engine/World.h"
#include "AtmosphericsSubSystem.generated.h"


/**
 * 
 */

UCLASS()
class VOXELATMOSPHERICS_API UAtmosphericsSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
	
	void CreateChunk(FIntVector ChunkCoords);
	void InitializeChunks();
	void DestroyChunks();
	
	UPROPERTY()
	FVector Origin;

	UPROPERTY()
	float VoxelSize = 100.0f; //size in U-Units (cm)

	UPROPERTY()
	float ChunkSize = 16 * VoxelSize;

	FIntVector ChunkExtents = FIntVector(10,10,10);

	UPROPERTY()
	bool Enabled = true;
	
	UPROPERTY()
	TMap<FIntVector,AVoxelChunk*> Chunks;
	
	
public:

	UFUNCTION()
	FIntVector WorldToChunkPos(FVector WorldPos);

	UFUNCTION()
	FVector ChunkPosToWorld(FIntVector ChunkPos);

	
	UFUNCTION()
	AVoxelChunk* GetChunk(FIntVector ChunkCoords);
	UFUNCTION()
	AVoxelChunk* GetChunkFromPos(FVector WorldPos);
	UFUNCTION()
	FIntVector GetChunkCoords(AVoxelChunk* ChunkToFind);
	UFUNCTION()
	FVector GetChunkWorldPos(AVoxelChunk* ChunkToFind);	
};
