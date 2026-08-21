// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/CPP_AbilitySystemComponent.h"
#include "CPP_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class FINALPROJECTUE09_API UCPP_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

    UCPP_AttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
    FGameplayAttributeData Health = 100.0f;
    ATTRIBUTE_ACCESSORS(UCPP_AttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
    FGameplayAttributeData Speed = 300.0f;
    ATTRIBUTE_ACCESSORS(UCPP_AttributeSet, Speed)


        UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
    FGameplayAttributeData MaxHealth = 100.0f;
    ATTRIBUTE_ACCESSORS(UCPP_AttributeSet, MaxHealth)

        UPROPERTY(BlueprintReadOnly, Category = "AttributeSet")
    FGameplayAttributeData MaxSpeed = 2000.0f;
    ATTRIBUTE_ACCESSORS(UCPP_AttributeSet, MaxSpeed)

        virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    
};
