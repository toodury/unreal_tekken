// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/RandomCharacter.h"

// Sets default values
ARandomCharacter::ARandomCharacter()
{
	RandomCharacter = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RandomCharacter"));
	RandomCharacter->SetText(TEXT("?"));
	RandomCharacter->SetHorizontalAlignment(EHTA_Center);
	RandomCharacter->SetVerticalAlignment(EVRTA_TextTop);
	RandomCharacter->SetWorldSize(100.0f);
	RandomCharacter->SetTextRenderColor(FColor(255, 0, 0, 1));
}

//// Called when the game starts or when spawned
//void ARandomCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ARandomCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void ARandomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

