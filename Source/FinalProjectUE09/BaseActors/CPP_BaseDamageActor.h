// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CPP_BaseDamageActor.generated.h"

UCLASS()
class FINALPROJECTUE09_API ACPP_BaseDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACPP_BaseDamageActor();

	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ProjectileLevel = 1.0f;

	UFUNCTION()
	float GetDamageActorLevel();

	float GetCurrentDamage() const;

protected:
	
	virtual void BeginPlay() override;
};
