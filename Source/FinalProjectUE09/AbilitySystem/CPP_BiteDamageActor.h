// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CPP_DamageActor.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "CPP_BiteDamageActor.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECTUE09_API ACPP_BiteDamageActor : public ACPP_DamageActor
{
	GENERATED_BODY()
	
public:

	ACPP_BiteDamageActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Radius = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DamageSetByCallerTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Pawn;

	void InitDamage(AActor* InSourceActor);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AActor* SourceActor = nullptr;

	void ApplyDamageOnce();

};
