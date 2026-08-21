// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActors/CPP_EnemyCaracter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

ACPP_EnemyCaracter::ACPP_EnemyCaracter()
{

}

void ACPP_EnemyCaracter::BeginPlay()
{
    Super::BeginPlay();

    
    UCharacterMovementComponent* iCharacterMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
    iCharacterMovement->MaxWalkSpeed = 2500.0f;
 
}

void ACPP_EnemyCaracter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (ASComponent)
    {
        ASComponent->AddLooseGameplayTags(StartupTags);
    }
}
