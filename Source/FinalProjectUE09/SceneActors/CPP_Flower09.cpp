// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneActors/CPP_Flower09.h"


ACPP_Flower09::ACPP_Flower09()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	FlowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlowerMesh"));
	FlowerMesh->SetupAttachment(RootComponent);
}
