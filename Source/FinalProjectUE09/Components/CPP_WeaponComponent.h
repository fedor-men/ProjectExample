// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_WeaponComponent.generated.h"

class ACPP_BaseCaracter;
class ACPP_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECTUE09_API UCPP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_WeaponComponent();

	UFUNCTION()
	void InitWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION()
	void ReloadWeapon();

	UFUNCTION()
	void NextWeapon();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void EqwipWeapon(int32 WeaponIndex);

	UFUNCTION()
	void AttachWeaponToSocket(ACPP_BaseWeapon*& WeaponToEquip, FName SocketName);

	UFUNCTION()
	void SpawnWeapon();

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	ACPP_BaseWeapon* CurrentWeapon = nullptr;

	//-----------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACPP_BaseCaracter* Owner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ACPP_BaseWeapon>> WeaponClass;

	UPROPERTY(BlueprintReadOnly)
	TArray <ACPP_BaseWeapon*> Weapons;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponArmorySocketName = "WeaponArmorySocket";

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName = "WeaponSocket";

protected:

	UPROPERTY()
	int32 CurrentWeaponIndex = 0;

};
