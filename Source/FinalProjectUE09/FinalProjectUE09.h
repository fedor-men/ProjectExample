// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FinalProjectUE09.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogFinalProjectUE09, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangetSignature, float, Health, float, DeltaHealth);


USTRUCT(BlueprintType)

struct FAmmoData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UE09/Weapon")
	int32 Bullits = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UE09/Weapon")
	int32 Clips = 5;
};