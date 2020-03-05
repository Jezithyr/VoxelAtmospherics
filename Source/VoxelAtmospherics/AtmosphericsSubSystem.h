// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VoxelChunk.h"
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
	float VoxelSize;

	UPROPERTY()
	TMap<FIntVector,AVoxelChunk> Chunks;
	
	
public:
	UFUNCTION()
	AVoxelChunk* GetChunk(FIntVector ChunkCoords);
	UFUNCTION()
	AVoxelChunk* GetChunkFromPos(FVector WorldPos);
	UFUNCTION()
	FIntVector GetChunkCoords(AVoxelChunk* ChunkToFind);
	UFUNCTION()
	FVector GetChunkWorldPos(AVoxelChunk* ChunkToFind);	
};
