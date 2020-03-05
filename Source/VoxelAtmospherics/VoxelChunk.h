// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Voxel.h"
#include "Gas.h"
#include "VoxelChunk.generated.h"


USTRUCT()
struct FVoxelGas //get around UPROPERTY nested container error
{
	GENERATED_BODY()
	
	UPROPERTY()
	TMap<FIntVector, float> Data;

	FVoxelGas()
	{
		
	}
};

USTRUCT()
struct FAtmoData
{
	GENERATED_BODY()
	
	UPROPERTY()
	AGas* GasPtr;
	
	UPROPERTY()
	float Mols;
	
	FAtmoData()
	{
		GasPtr = nullptr;
		Mols = 0.0f;
	}

	FAtmoData(AGas* g,float m)
	{
		GasPtr = g;
		Mols = m;
	}
};



USTRUCT(BlueprintType)
struct FVoxelData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int BlockHP;
	
	UPROPERTY(BlueprintReadWrite)
	bool bAirTight;
	
	UPROPERTY()
	AVoxel* Voxel;

	FVoxelData()
	{
		Voxel = nullptr;
		BlockHP = 0;
		bAirTight = false;
	}
	
	FVoxelData(UINT16 hp,bool at, AVoxel* v)
	{
		BlockHP = hp;
		bAirTight = at;
		Voxel = v;
	}

	~FVoxelData() //destructor
	{
		delete Voxel;
	}
};


UCLASS()
class VOXELATMOSPHERICS_API AVoxelChunk : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AVoxelChunk();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:

	UPROPERTY()
	TMap<AGas*, FVoxelGas> GasData;

	
public:	
	// Called every frame


	//gas type operations
	UFUNCTION(BlueprintCallable)
	bool ContainsGasType(AGas* gas);
	
	UFUNCTION(BlueprintCallable)
	void AddGasType(AGas* gas);
	
	UFUNCTION(BlueprintCallable)
	void RemoveGasType(AGas* gas);
	
	UFUNCTION(BlueprintCallable)
	void AddGasToCell(AGas* gas, FIntVector VoxelPos,float Mols);
	
	UFUNCTION(BlueprintCallable)
	void SetGasInCell(AGas* gas, FIntVector VoxelPos, float Mols);
	
	UFUNCTION(BlueprintCallable)
	float RemoveGasInCell(AGas* gas, FIntVector VoxelPos, float Mols);
	
	UFUNCTION(BlueprintCallable)
	bool TransferGas(AGas* gas, FIntVector VoxelPosOrig, FIntVector VoxelPosNew, float Mols);
	
	UFUNCTION(BlueprintCallable)
	void DelGasFromCell(AGas* gas, FIntVector VoxelPos, float Mols);
	
	void Tick(float DeltaTime) override;
	
	FVoxelData Data[16][16][16]; //3d array because fuck using ustructs for it. This will probably break some shit.

	
};
