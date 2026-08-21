// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseActors/CPP_BaseDamageActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "CPP_BaseProjectileActor.generated.h"

UCLASS()
class FINALPROJECTUE09_API ACPP_BaseProjectileActor : public ACPP_BaseDamageActor
{
	GENERATED_BODY()
	
public:

	ACPP_BaseProjectileActor();

	UPROPERTY()
	FTimerHandle DestoyTimer;
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (EditAnywhere))
	USphereComponent* DamageSphere;

	UFUNCTION()
	void DestroyProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void BeginPlay();
};
