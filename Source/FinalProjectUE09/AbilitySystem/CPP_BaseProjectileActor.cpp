// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CPP_BaseProjectileActor.h"


ACPP_BaseProjectileActor::ACPP_BaseProjectileActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = DamageSphere;

	DamageSphere->InitSphereRadius(100.0f);
	
	DamageSphere->SetSimulatePhysics(false);
	DamageSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageSphere->SetCollisionProfileName(TEXT("ProjectileMesh"));

	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = DamageSphere;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	DamageSphere->OnComponentHit.AddDynamic(this, &ACPP_BaseProjectileActor::OnHit);
}





void ACPP_BaseProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UAbilitySystemComponent* TargetASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();

	if (TargetASC && DamageEffectClass.Get())
	{

		FGameplayEffectContextHandle Context = TargetASC->MakeEffectContext();
		Context.AddSourceObject(this);
		Context.AddInstigator(GetInstigator(), this);

		FGameplayEffectSpecHandle Spec = TargetASC->MakeOutgoingSpec(
			DamageEffectClass,
			ProjectileLevel,
			Context
		);

		if (Spec.IsValid())
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
            Destroy();
		}
        float length = 20.0f;
	    for (size_t i = 0; i > length; i++)
	    {
		    this->Destroy();
	    }
	}
	
	
}

void ACPP_BaseProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Direction = GetActorForwardVector();
	{
		ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	}
	GetWorldTimerManager().SetTimer(DestoyTimer, this, &ACPP_BaseProjectileActor::DestroyProjectile, 1.0, false, 10.0);
}

void ACPP_BaseProjectileActor::DestroyProjectile()
{
	this->Destroy();
}