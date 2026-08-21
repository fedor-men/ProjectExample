// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActors/CPP_BaseCaracter.h"
#include "AbilitySystem/CPP_AttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystem/CPP_AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACPP_BaseCaracter::ACPP_BaseCaracter()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPP_BaseCaracter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACPP_BaseCaracter::OnOverlapEnd);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	WeaponComponent = CreateDefaultSubobject<UCPP_WeaponComponent>(TEXT("WeaponComponent"));
	ASComponent = CreateDefaultSubobject<UCPP_AbilitySystemComponent>(TEXT("AbilitySistem"));
	Attributes = CreateDefaultSubobject<UCPP_AttributeSet>(TEXT("AttributeSet"));
}


void ACPP_BaseCaracter::BeginPlay()
{
	Super::BeginPlay();

	if (Attributes)
	{
		ASComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddUObject(this, &ACPP_BaseCaracter::OnHealthChangedNative);
	}

}



void ACPP_BaseCaracter::OnHealthChangedNative(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f && !bIsDeath)
	{
		bIsDeath = true;
		CharacterDead();
	}
}

void ACPP_BaseCaracter::InitAbility(TSubclassOf<class UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (!ASComponent || !AbilityToGet)
	{
		return;
	}
	ASComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, -1));
}

void ACPP_BaseCaracter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ASComponent)
	{
		ASComponent->InitAbilityActorInfo(this, this);
	}

}





float ACPP_BaseCaracter::GetCaracterLevel()
{
	return CaracterLevel;
}



void ACPP_BaseCaracter::CharacterDead()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	bIsDeath = true;
}

void ACPP_BaseCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//-------------------------------

void ACPP_BaseCaracter::OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPP_DamageActor* lDamage = Cast<ACPP_DamageActor>(OtherActor);

	if (!lDamage || OtherActor == this)
	{
		return;
	}

  for (const FActiveDamageEffect& Effect : ActiveDamageEffects)
  {
	  if (Effect.SourceActor == OtherActor)
	  {
		  return;
	  }
  }

  if (!lDamage->DamageEffectClass.Get())
  {
	  return;
  }
		float CurrentLevel = lDamage->GetDamageActorLevel();
		FGameplayEffectContextHandle Context = ASComponent->MakeEffectContext();
		Context.AddInstigator(GetInstigator(), OtherActor);
		Context.AddHitResult(SweepResult);
		FGameplayEffectSpecHandle Spec = ASComponent->MakeOutgoingSpec(lDamage->DamageEffectClass, CurrentLevel, Context);
		FActiveGameplayEffectHandle NewHandle;

		if (Spec.IsValid() && Spec.Data.IsValid())
		{
			NewHandle = ASComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
			if (NewHandle.IsValid())
			{
				
				FActiveDamageEffect DamageEntry;
				DamageEntry.SourceActor = OtherActor;
				DamageEntry.Handle = NewHandle;
				ActiveDamageEffects.Add(DamageEntry);
			}
		}
}



void ACPP_BaseCaracter::OnOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	for (int32 i = 0; i < ActiveDamageEffects.Num(); ++i)
	{
		if (ActiveDamageEffects[i].SourceActor == OtherActor)
		{
			ASComponent->RemoveActiveGameplayEffect(ActiveDamageEffects[i].Handle);
			ActiveDamageEffects.RemoveAt(i);
			return;
		}
	}
}

