// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CPP_BarrelComponent.h"


ACPP_BarrelComponent::ACPP_BarrelComponent()
{
 	
	PrimaryActorTick.bCanEverTick = true;
}


void ACPP_BarrelComponent::SpawnProjectile()
{
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    ACPP_BaseProjectileActor* Projectile = GetWorld()->SpawnActor<ACPP_BaseProjectileActor>(
        ProjectileClass, SpawnLocation, SpawnRotation);

    if (Projectile && Projectile->ProjectileMovement)
    {
        FVector Direction = SpawnRotation.Vector();
        Projectile->ProjectileMovement->Velocity = Direction * SpeedMove;
    }
}

void ACPP_BarrelComponent::BeginPlay()
{
	Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ACPP_BarrelComponent::SpawnProjectile, TimeBetweenSpawn, true, 0.0f);
}


void ACPP_BarrelComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

