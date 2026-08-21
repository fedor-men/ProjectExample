// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActors/CPP_BaseCaracter.h"
#include "AbilitySystem/CPP_BiteDamageActor.h"
#include "AbilitySystem/CPP_AbilitySystemComponent.h"
#include "CPP_EnemyCaracter.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECTUE09_API ACPP_EnemyCaracter : public ACPP_BaseCaracter
{
	GENERATED_BODY()
	
public:

	ACPP_EnemyCaracter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY()
	TObjectPtr<ACPP_BiteDamageActor> BiteDamageActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer StartupTags;
};
