// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CPP_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseActors/CPP_BaseCaracter.h"

UCPP_AttributeSet::UCPP_AttributeSet()
{

}

void UCPP_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float CurrentMax = GetMaxHealth();
		const float CurrentHealth = GetHealth();
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, CurrentMax));
		const float NewHealth = GetHealth();
		ACPP_BaseCaracter* OwnerChar = Cast <ACPP_BaseCaracter>(GetOwningActor());
	}
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(FMath::Clamp(GetSpeed(), 0.0f, GetMaxSpeed()));
	}
}
