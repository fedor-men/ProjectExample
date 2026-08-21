// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActors/CPP_BaseCaracter.h"
#include "CPP_MainPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
UCLASS()

class FINALPROJECTUE09_API ACPP_MainPlayerCharacter : public ACPP_BaseCaracter
{
	GENERATED_BODY()
public:

     ACPP_MainPlayerCharacter();

	 FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	 FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	 void OnRun(bool OnRunBool);

	 float AxelRunFunc();

	 void StopAxelRunFunc();


	 UPROPERTY(EditDefaultsOnly)
	 UStaticMeshComponent* Cell;

	 UFUNCTION()
	 void StartFire();

	 UFUNCTION()
	 void StopFire();

	 UFUNCTION()
	 void NextWeapon();

	 UPROPERTY(BlueprintReadWrite)
	 bool MoveReload = false;

	 UPROPERTY()
	 bool RunBool = false;

protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Zoom(bool bizZooming);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(BlueprintReadWrite)
	float MoveValue;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "56_Input")
	UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, Category = "56_Input")
	UInputAction* ShootingAction;

	UPROPERTY(EditAnywhere, Category = "56_Input")
	UInputAction* AxelRun;

	UPROPERTY(EditAnywhere, Category = "56_Input")
	UInputAction* NextWeapponAction;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	
};
