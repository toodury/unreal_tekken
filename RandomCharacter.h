// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TextRenderComponent.h"
#include "RandomCharacter.generated.h"

UCLASS()
class TEKKEN_API ARandomCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARandomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ·£´ýÀ» °ñ¶úÀ» ¶§ ¶ç¿ï ¹°À½Ç¥
	UPROPERTY()
	UTextRenderComponent* RandomCharacter;

};
