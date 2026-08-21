// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActors/CPP_MainPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/CPP_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "FinalProjectUE09.h"


ACPP_MainPlayerCharacter::ACPP_MainPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	Cell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cell"));
	Cell->SetupAttachment(FollowCamera);
}


void ACPP_MainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(AxelRun, ETriggerEvent::Started, this, &ACPP_MainPlayerCharacter::OnRun, true);
		EnhancedInputComponent->BindAction(AxelRun, ETriggerEvent::Completed, this, &ACPP_MainPlayerCharacter::StopAxelRunFunc);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPP_MainPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACPP_MainPlayerCharacter::Look);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPP_MainPlayerCharacter::Look);

		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &ACPP_MainPlayerCharacter::Zoom, true);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Completed, this, &ACPP_MainPlayerCharacter::Zoom, false);

		EnhancedInputComponent->BindAction(ShootingAction, ETriggerEvent::Started, this, &ACPP_MainPlayerCharacter::StartFire);
		EnhancedInputComponent->BindAction(ShootingAction, ETriggerEvent::Completed, this, &ACPP_MainPlayerCharacter::StopFire);

		EnhancedInputComponent->BindAction(NextWeapponAction, ETriggerEvent::Completed, this, &ACPP_MainPlayerCharacter::NextWeapon);
	}
	
}


void ACPP_MainPlayerCharacter::Zoom(bool bizZooming)
{
	if (bizZooming)
	{
		DoFire = true;
		FollowCamera->SetFieldOfView(20.0f);
	}
	else
	{
		DoFire = false;
		FollowCamera->SetFieldOfView(90.0f);
	}
}


void ACPP_MainPlayerCharacter::OnRun(bool OnRunBool)
{
	if (OnRunBool)
	{
		RunBool = true;
	}
}

float ACPP_MainPlayerCharacter::AxelRunFunc()
{
	if (MoveValue > 0 && RunBool == true)
	{
		StopFire();
		return MaxSpeed * 2;
	}
	if (MoveValue < 0 && RunBool == false)
	{
		return MaxSpeed;
	}
	return MaxSpeed;
}


void ACPP_MainPlayerCharacter::StopAxelRunFunc()
{
	UCharacterMovementComponent* iCharacterMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	iCharacterMovement->MaxWalkSpeed = MaxSpeed;
	RunBool = false;
}


void ACPP_MainPlayerCharacter::StartFire()
{
	if (!WeaponComponent && DoFire == false)
	{
		return;
	}
	if (DoFire == true)
	{
		bUseControllerRotationYaw = true;
		WeaponComponent->StartFire();
	}
}

void ACPP_MainPlayerCharacter::StopFire()
{
	if (!WeaponComponent)
	{
		return;
	}
	bUseControllerRotationYaw = false;
	WeaponComponent->StopFire();
}


void ACPP_MainPlayerCharacter::NextWeapon()
{
	WeaponComponent->NextWeapon();
}



void ACPP_MainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponComponent)
	{
		WeaponComponent->InitWeaponComponent();
	}
}



void ACPP_MainPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	MoveValue = MovementVector.Y;

	UCharacterMovementComponent* iCharacterMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	iCharacterMovement->MaxWalkSpeed = AxelRunFunc();

	if (GetController() != nullptr && MoveReload == false)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACPP_MainPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (GetController() != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


