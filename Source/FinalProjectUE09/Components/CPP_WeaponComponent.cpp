// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CPP_WeaponComponent.h"
#include "BaseActors/CPP_BaseCaracter.h"
#include "BaseActors/CPP_BaseWeapon.h"



UCPP_WeaponComponent::UCPP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


void UCPP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCPP_WeaponComponent::InitWeaponComponent()
{
	Owner = Cast<ACPP_BaseCaracter>(GetOwner());
	if (!Owner)
	{
		return;
	}
	SpawnWeapon();
	EqwipWeapon(CurrentWeaponIndex);
}

void UCPP_WeaponComponent::StartFire()
{
	if (!CurrentWeapon || Owner->bIsDeath == true)
	{
		StopFire();
		return;
	}
	CurrentWeapon->lStartFire();
}

void UCPP_WeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->lStopFire();
}

void UCPP_WeaponComponent::ReloadWeapon()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->ReloadWeapon();
}

void UCPP_WeaponComponent::NextWeapon()
{
	if (Weapons.IsEmpty())
		return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EqwipWeapon(CurrentWeaponIndex);
}



void UCPP_WeaponComponent::EqwipWeapon(int32 WeaponIndex)
{
	if (Weapons.IsEmpty() || !Weapons.IsValidIndex(WeaponIndex))
	{
		return;
	}
	ACPP_BaseWeapon* lNewWeapon = Weapons[WeaponIndex];
	if (!IsValid(lNewWeapon))
		return;
	if (IsValid(CurrentWeapon) && CurrentWeapon != lNewWeapon)
	{
		CurrentWeapon->lStopFire();
		AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocketName);

	}
	CurrentWeapon = lNewWeapon;
	AttachWeaponToSocket(CurrentWeapon, WeaponSocketName);
	CurrentWeaponIndex = WeaponIndex;
}


void UCPP_WeaponComponent::AttachWeaponToSocket(ACPP_BaseWeapon*& WeaponToEquip, FName SocketName)
{
	auto lCharMesh = Owner->GetMesh();

	if (!lCharMesh || !WeaponToEquip)
		return;
	FAttachmentTransformRules lAttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToEquip->AttachToComponent(lCharMesh, lAttachmentRules, SocketName);
}


void UCPP_WeaponComponent::SpawnWeapon()
{
	if (!GetWorld())return;
	for (auto lWeaponClass : WeaponClass)
	{
		if (!lWeaponClass)
			continue;
		ACPP_BaseWeapon* lSpawnedWeapon = GetWorld()->SpawnActor<ACPP_BaseWeapon>(lWeaponClass);
		if (!lSpawnedWeapon)
			continue;
		lSpawnedWeapon->SetOwner(Owner);
		AttachWeaponToSocket(lSpawnedWeapon, WeaponArmorySocketName);
		Weapons.Add(lSpawnedWeapon);
	}
}
