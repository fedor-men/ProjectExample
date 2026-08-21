// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystem/CPP_BaseProjectileActor.h"
#include "CPP_BarrelComponent.generated.h"

UCLASS()
class FINALPROJECTUE09_API ACPP_BarrelComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACPP_BarrelComponent();

	UPROPERTY()
	ACPP_BaseProjectileActor* ProjectileActor;

	UFUNCTION()
	void SpawnProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Final Projectile")
	TSubclassOf<ACPP_BaseProjectileActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Final Projectile")
	float TimeBetweenSpawn = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle ShotTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Final Projectile")
	float SpeedMove = 100.0f;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
