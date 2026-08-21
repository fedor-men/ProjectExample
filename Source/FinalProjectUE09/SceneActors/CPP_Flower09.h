// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActors/CPP_BaseActor09.h"

#include "Components/SceneComponent.h"
#include "CPP_Flower09.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECTUE09_API ACPP_Flower09 : public ACPP_BaseActor09
{
	GENERATED_BODY()
	
public:

	ACPP_Flower09();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* FlowerMesh;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* Root;
};
