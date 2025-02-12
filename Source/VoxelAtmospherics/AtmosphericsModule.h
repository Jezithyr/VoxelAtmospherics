// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AtmosphericsModule.generated.h"

/**
 * 
 */
UCLASS()
class VOXELATMOSPHERICS_API UAtmosphericsModule : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
};
