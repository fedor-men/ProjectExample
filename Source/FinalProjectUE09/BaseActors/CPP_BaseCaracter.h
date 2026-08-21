// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"

#include "GameplayEffectTypes.h"
#include "Logging/LogMacros.h"
#include "AbilitySystem/CPP_DamageActor.h"
#include "Components/CPP_WeaponComponent.h"


#include "CPP_BaseCaracter.generated.h"


struct FActiveDamageEffect
{
	AActor* SourceActor = nullptr;
	FActiveGameplayEffectHandle Handle;
};

UCLASS()

class FINALPROJECTUE09_API ACPP_BaseCaracter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACPP_BaseCaracter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCPP_AbilitySystemComponent* ASComponent;

	UPROPERTY(EditDefaultsOnly)
	UCPP_WeaponComponent* WeaponComponent;

	TArray<FActiveDamageEffect> ActiveDamageEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attrebutes")
	class UCPP_AttributeSet* Attributes;

	void OnHealthChangedNative(const FOnAttributeChangeData& );

	UFUNCTION(BlueprintCallable)
	void InitAbility(TSubclassOf<class UGameplayAbility> AbilityToGet, int32 AbilityLevel);

	
	virtual void PossessedBy(AController* NewController);

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	float MaxSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attrebutes")
	float CaracterLevel = 1.0f;

	UFUNCTION()
	float GetCaracterLevel();

	UPROPERTY()
	float NewHealthValue;

	UFUNCTION()
	void CharacterDead();
	
public:	

	UPROPERTY(BlueprintReadOnly)
	bool DoFire = false;
	
    UPROPERTY(BlueprintReadOnly)
	bool bIsDeath = false;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

};
