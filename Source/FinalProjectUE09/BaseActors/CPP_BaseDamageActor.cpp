// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActors/CPP_BaseDamageActor.h"



ACPP_BaseDamageActor::ACPP_BaseDamageActor()
{	
	PrimaryActorTick.bCanEverTick = true;
	
}


float ACPP_BaseDamageActor::GetDamageActorLevel()
{
	return ProjectileLevel;
}

float ACPP_BaseDamageActor::GetCurrentDamage() const
{
	return 0.0f;
}

void ACPP_BaseDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}


