// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystem/CPP_BiteDamageActor.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_AnimNotify_SpawnBiteDamage.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECTUE09_API UCPP_AnimNotify_SpawnBiteDamage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FName MouthSocketName = TEXT("MouthSocket");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<ACPP_BiteDamageActor> DamageActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Radius = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DamageSetByCallerTag;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:

	
};
