// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "NinjaCharacter.generated.h"

/**
 * 
 */

UCLASS()
class TEKKEN_API ANinjaCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:

	// 닌자 캐릭터
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
