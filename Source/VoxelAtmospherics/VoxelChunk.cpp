// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"

// Sets default values
AVoxelChunk::AVoxelChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AVoxelChunk::ContainsGasType(AGas* gas)
{
	return GasData.Contains(gas);	
}

void AVoxelChunk::AddGasType(AGas* gas) //don't use this
{
	GasData.FindOrAdd(gas);
}

void AVoxelChunk::RemoveGasType(AGas* gas)//this deletes the entire gas cell table
{
	GasData.FindAndRemoveChecked(gas);
}

void AVoxelChunk::AddGasToCell(AGas* gas,FIntVector voxelPos,float Mols)
{
	TMap<FIntVector, float> GasCells = GasData.FindOrAdd(gas).Data;
	auto OldMols = GasCells.FindOrAdd(voxelPos);
	OldMols += Mols;
}

void AVoxelChunk::SetGasInCell(AGas* gas, FIntVector voxelPos, float Mols)
{
	TMap<FIntVector, float> GasCells = GasData.FindOrAdd(gas).Data;;

	if (Mols <= 0)
	{
		GasCells.Remove(voxelPos);
	}
	else
	{
		auto NewMols = GasCells.FindOrAdd(voxelPos);
		NewMols = Mols;
	}
}

float AVoxelChunk::RemoveGasInCell(AGas* gas, FIntVector VoxelPos, float Mols)
{
	TMap<FIntVector, float> GasCells = GasData.FindRef(gas).Data;
	if (GasCells.Num() == 0) return false;
	float* NewMols = GasCells.Find(VoxelPos);
	*NewMols -= Mols;
	if (*NewMols < 0)
	{
		*NewMols = 0;
		return -*NewMols;
	}
	return 0;
}

bool AVoxelChunk::TransferGas(AGas* gas, FIntVector VoxelPosOrig, FIntVector VoxelPosNew, float Mols)
{
	const float Underflow = RemoveGasInCell(gas, VoxelPosOrig,Mols);
	AddGasToCell(gas, VoxelPosNew, Mols - Underflow);
	
	return Underflow == 0;
}

void AVoxelChunk::DelGasFromCell(AGas* gas, FIntVector VoxelPos, float Mols)
{
	AddGasToCell(gas, VoxelPos, Mols);
}


// Called every frame
void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

