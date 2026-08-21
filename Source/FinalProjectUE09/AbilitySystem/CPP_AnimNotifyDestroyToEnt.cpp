// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CPP_AnimNotifyDestroyToEnt.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PlayerActors/CPP_EnemyCaracter.h"

void UCPP_AnimNotifyDestroyToEnt::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor) return;

	ACPP_EnemyCaracter* Nessy = Cast<ACPP_EnemyCaracter>(OwnerActor);
	if (!Nessy) return;

	if (Nessy->BiteDamageActor)
	{
		Nessy->BiteDamageActor->Destroy();
		Nessy->BiteDamageActor = nullptr;
	}
}
