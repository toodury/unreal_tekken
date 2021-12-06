// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodCharacter.h"

AWoodCharacter::AWoodCharacter()
{
	// ���� ĳ������ ������ �� �̸� ����
	// ������ �޼�, �޹�, �������� �������Ʈ���� ����
	RightHandSocketName = FName(TEXT("Bone004"));

	// Character Detail ���� �ʱ�ȭ
	InitializeCharacterDetail();

	// Attack Table �ʱ�ȭ
	InitializeAttackTable();

	// Hit Table �ʱ�ȭ
	InitializeHitTable();

	// �� ĳ���� Ŭ���� �����ڿ��� �ʼ������� �����ؾ� �� �Լ� ����
	CharacterClassCommonConstructor();
}

void AWoodCharacter::InitializeCharacterDetail()
{
	CharacterID = ECharacters::Wood;
	CharacterName = FName(TEXT("Wood"));
	AttackRange = 80;
}

void AWoodCharacter::InitializeAttackTable()
{
	//TArray<EInputKey> AttackMotion;

	//AttackMotion.Emplace(EInputKey::LeftPunch);
	//AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Attack"));

	AttackMotionTable.Emplace(TEXT("H"), TEXT("Attack"));

	AttackMotionBoolTable.Emplace(TEXT("Attack"), false);

	FinalAttackMotions.Emplace(TEXT("Attack"));

	AttackMotionDamageTable.Emplace(TEXT("Attack"), 5.0f);
}

void AWoodCharacter::InitializeHitTable()
{
	AMyCharacter::InitializeHitTable();

	AttackMotionHitPositionTable.Emplace(TEXT("Attack"), EHitPosition::LeftArm);

	AttakMotionCollisionComponentTable.Emplace(TEXT("Attack"), RightHandCollision);
}