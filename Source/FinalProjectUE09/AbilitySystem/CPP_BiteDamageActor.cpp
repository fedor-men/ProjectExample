// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CPP_BiteDamageActor.h"
#include "Engine/OverlapResult.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Kismet/GameplayStatics.h"

ACPP_BiteDamageActor::ACPP_BiteDamageActor()
{

}



void ACPP_BiteDamageActor::InitDamage(AActor* InSourceActor)
{
	SourceActor = InSourceActor;
}



void ACPP_BiteDamageActor::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		Destroy();
		return;
	}

	ApplyDamageOnce();
}



void ACPP_BiteDamageActor::ApplyDamageOnce()
{
	if (!SourceActor)
	{
		return;
	}

	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (!SourceASC)
	{
		return;
	}

	
	if (!DamageEffectClass)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}


	const FVector Center = GetActorLocation();
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(BiteDamage), false, SourceActor);
	QueryParams.AddIgnoredActor(SourceActor);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	TArray<FOverlapResult> Overlaps;
	const bool bAny = World->OverlapMultiByObjectType( Overlaps, Center, FQuat::Identity, ObjectParams, SphereShape, QueryParams);

	if (!bAny)
	{
		return;
	}
		
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* TargetActor = Overlap.GetActor();
		if (!TargetActor || TargetActor == SourceActor)
		{
			continue;
		}
	
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (!TargetASC)
		{
			continue;
		}

		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		ContextHandle.AddSourceObject(SourceActor);

		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, ProjectileLevel, ContextHandle);

		if (!SpecHandle.IsValid() || !SpecHandle.Data.IsValid())
		{
			continue;
		}

		SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}
}
