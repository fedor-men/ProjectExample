// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActors/CPP_BaseWeapon.h"
#include "Components/CPP_WeaponComponent.h"


ACPP_BaseWeapon::ACPP_BaseWeapon()
{	
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(" MeshObject");
	SetRootComponent(WeaponMesh);

}


void ACPP_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	CurrentAmmo = DefaultAmmo;
}


void ACPP_BaseWeapon::lStartFire()
{
	if (CurrentAmmo.Bullits > 0 && Reload == false)
	{
		GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ACPP_BaseWeapon::MakeShot, TimeBetweenShots, true, 0.0f);
	}
	if (CurrentAmmo.Clips != 0 && CurrentAmmo.Bullits == 0)
	{
		ReloadWeapon();
	}
}


void ACPP_BaseWeapon::lStopFire()
{
	NumShoot = 0;
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ACPP_BaseWeapon::MakeShot()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor) return;
	UStaticMeshComponent* Cell = OwnerActor->FindComponentByClass<UStaticMeshComponent>();

	if (!Cell) return;
	const FTransform SpawnTransform = Cell->GetComponentTransform();

	FActorSpawnParameters Params;
	Params.Owner = OwnerActor;
	Params.Instigator = Cast<APawn>(OwnerActor);

	if (NumShoot < ChangeTemp && CurrentAmmo.Bullits > 0)
	{
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>( ProjectileSpawn, SpawnTransform, Params );
		WeaponMesh->PlayAnimation(FireAnim, false);
		NumShoot++;
		DecreaceAmmo();
	}
}



void ACPP_BaseWeapon::ReloadWeapon()
{
	if (IsClipEmpty())
	{
		bIsNeedAmmo = true;
		return;
	}
	if (CurrentAmmo.Bullits == DefaultAmmo.Bullits)
	{
		return;
	}
	bIsNeedAmmo = false;
	Reload = true;
	ReloadInProgress = true;
	WeaponMesh->PlayAnimation(ReloadAnim, false);
	float IReloadAnimTime = ReloadAnim->GetPlayLength();

	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ACPP_BaseWeapon::SwitchisReload, 1.0f, false, IReloadAnimTime);
	CurrentAmmo.Clips--;
	CurrentAmmo.Bullits = DefaultAmmo.Bullits;
}


bool ACPP_BaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Clips == 0;
}


bool ACPP_BaseWeapon::IsCanReload() const
{
	return false;
}


void ACPP_BaseWeapon::DecreaceAmmo()
{
	CurrentAmmo.Bullits--;
	if (CurrentAmmo.Bullits == 0)
	{
		lStopFire();
		ReloadWeapon();
	}
}

void ACPP_BaseWeapon::SwitchisReload()
{
	ReloadInProgress = !ReloadInProgress;
	Reload = false;
}


bool ACPP_BaseWeapon::AddAmmo(FAmmoData AmmoToAdd)
{
	if (CurrentAmmo.Clips == DefaultAmmo.Clips)
	{
		bIsNeedAmmo = false;
		return false;
	}

	if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		if (CurrentAmmo.Clips + AmmoToAdd.Clips >= DefaultAmmo.Clips)
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			bIsNeedAmmo = false;
		}
		else
		{
			CurrentAmmo.Clips = +AmmoToAdd.Clips;
			bIsNeedAmmo = false;
		}
		return true;
	}
	return false;
}



