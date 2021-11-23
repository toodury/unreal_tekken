// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "WoodCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API AWoodCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:

	AWoodCharacter();

	// Character Detail
	// 나무 캐릭터 변수 초기화
	virtual void InitializeCharacterDetail() override;

	// Attack
	// 나무 캐릭터 Attack Table 초기화
	virtual void InitializeAttackTable() override;

	// Hit
	// 나무 캐릭터 Hit Table 초기화
	virtual void InitializeHitTable() override;
	
};
