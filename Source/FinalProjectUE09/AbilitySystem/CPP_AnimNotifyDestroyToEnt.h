// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_AnimNotifyDestroyToEnt.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "ANS Destroy Bite Damage Actor"))
class FINALPROJECTUE09_API UCPP_AnimNotifyDestroyToEnt : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
