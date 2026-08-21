// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_BaseActor09.generated.h"

UCLASS()
class FINALPROJECTUE09_API ACPP_BaseActor09 : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACPP_BaseActor09();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
