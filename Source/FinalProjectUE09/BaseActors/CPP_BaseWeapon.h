// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalProjectUE09.h"
#include "AbilitySystem/CPP_BaseProjectileActor.h"


#include "CPP_BaseWeapon.generated.h"

class UCPP_WeaponComponent;

UCLASS()
class FINALPROJECTUE09_API ACPP_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACPP_BaseWeapon();

	void lStartFire();

	UFUNCTION(BlueprintCallable)
	void lStopFire();

	void ReloadWeapon();
	bool IsClipEmpty()const;
	bool IsCanReload()const;
	void DecreaceAmmo();
	void MakeShot();
	void SwitchisReload();

	UPROPERTY()
	ACPP_BaseProjectileActor* ProjectileActor;

	UPROPERTY(EditDefaultsOnly, Category = "Final Projectile")
	TSubclassOf<ACPP_BaseProjectileActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "56/Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "56/ Weapon")
	TSubclassOf<AActor>ProjectileSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Final Projectile")
	float SpeedMove = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsNeedAmmo = false;

	UFUNCTION(BlueprintCallable)
	bool AddAmmo(FAmmoData AmmoToAdd);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FAmmoData GetCurrentAmmo() const
	{
		return CurrentAmmo;
	};

protected:
	
	virtual void BeginPlay() override;

	bool ReloadInProgress = true;

	UPROPERTY(BlueprintReadWrite)
	int ChangeTemp = 1000;

	UPROPERTY()
	int NumShoot = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "56/Weapon")
	UAnimationAsset* FireAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "56/Weapon")
	UAnimationAsset* ReloadAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "56/Weapon")
	float TimeBetweenShots = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "56/Weapon")
	bool Reload = false;

	UPROPERTY(BlueprintReadOnly, Category = "56/Weapon")
	FTimerHandle ShotTimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "56/Weapon")
	FTimerHandle ReloadTimerHandle;


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "56/Weapon")
	FAmmoData DefaultAmmo{ 30, 4 };

protected:

	UPROPERTY(BlueprintReadWrite)
	FAmmoData CurrentAmmo;
};
