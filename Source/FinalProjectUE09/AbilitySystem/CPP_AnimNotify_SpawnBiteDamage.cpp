// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CPP_AnimNotify_SpawnBiteDamage.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PlayerActors/CPP_EnemyCaracter.h"

void UCPP_AnimNotify_SpawnBiteDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !DamageActorClass)
	{
		return;
	}

	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		return;
	}

	UWorld* World = MeshComp->GetWorld();
	if (!World)
	{
		return;
	}

	ACPP_EnemyCaracter* Nessy = Cast<ACPP_EnemyCaracter>(OwnerActor);

	if (!Nessy)	return;

	if (!MeshComp->DoesSocketExist(MouthSocketName))
	{
		return;
	}

	const FVector SpawnLocation = MeshComp->GetSocketLocation(MouthSocketName);
	const FRotator SpawnRotation = MeshComp->GetSocketRotation(MouthSocketName);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.Instigator = OwnerActor->GetInstigator();

	
	if (!IsValid(Nessy->BiteDamageActor))
	{
		ACPP_BiteDamageActor* DamageActor = World->SpawnActor<ACPP_BiteDamageActor>(DamageActorClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (!DamageActor)
		{
			return;
		}

		DamageActor->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, MouthSocketName);

		DamageActor->Radius = Radius;
		DamageActor->DamageEffectClass = DamageEffectClass;
		DamageActor->DamageSetByCallerTag = DamageSetByCallerTag;
		DamageActor->InitDamage(OwnerActor);
		Nessy->BiteDamageActor = DamageActor;
	}
}
