// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "NinjaCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAttackMotion : uint8 {
	LeftJap UMETA(DisplayName = "LeftJap"),
	LeftHook UMETA(DisplayName = "LeftHook"),
	SpinningBackfist UMETA(DisplayName = "SpinningBackfist"),
	RightCross UMETA(DisplayName = "RightCross"),
	RightUppercut UMETA(DisplayName = "RightUppercut"),
	ObliqueKick UMETA(DisplayName = "ObliqueKick"),
	StraightKick UMETA(DisplayName = "StraightKick"),
	LowRightThaiKick UMETA(DisplayName = "LowRightThaiKick"),
	CutDownKick UMETA(DisplayName = "CutDownKick"),
	WheelKick UMETA(DisplayName = "WheelKick")
};

UCLASS()
class TEKKEN_API ANinjaCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:

	ANinjaCharacter();

	// Character Detail
	// 닌자 캐릭터 변수 초기화
	virtual void InitializeCharacterDetail() override;

	// Attack
	// 닌자 캐릭터 Attack Table 초기화
	virtual void InitializeAttackTable() override;

	// Hit
	// 닌자 캐릭터 Hit Table 초기화
	virtual void InitializeHitTable() override;
};
