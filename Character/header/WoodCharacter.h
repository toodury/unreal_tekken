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

	// ���� ĳ����
	AWoodCharacter();

	// Character Detail
	// ���� ĳ���� ���� �ʱ�ȭ
	virtual void InitializeCharacterDetail() override;

	// Attack
	// ���� ĳ���� Attack Table �ʱ�ȭ
	virtual void InitializeAttackTable() override;

	// ���� ĳ������ ���� ���� �Լ� ������
	virtual void RandomAttack() override;

	// Hit
	// ���� ĳ���� Hit Table �ʱ�ȭ
	virtual void InitializeHitTable() override;
	
};
