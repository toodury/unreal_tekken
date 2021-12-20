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
	MaxAttackRange = 80;
	MinAttackRange = 60;
}

void AWoodCharacter::InitializeAttackTable()
{
	//TArray<EInputKey> AttackMotion;

	//AttackMotion.Emplace(EInputKey::LeftPunch);
	//AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Attack"));

	AttackMotionTable.Emplace(TEXT("H"), EAttackMotion::Wood__RightHandAttack);

	AttackMotionBoolTable.Emplace(EAttackMotion::Wood__RightHandAttack, false);

	FinalAttackMotions.Emplace(EAttackMotion::Wood__RightHandAttack);

	AttackMotionDamageTable.Emplace(EAttackMotion::Wood__RightHandAttack, 5.0f);
}

void AWoodCharacter::RandomAttack()
{
	WhenLeftPunchKeyClicked();
	UE_LOG(LogTemp, Log, TEXT("Wood Attack"));
}

void AWoodCharacter::InitializeHitTable()
{
	AMyCharacter::InitializeHitTable();

	AttackMotionHitPositionTable.Emplace(EAttackMotion::Wood__RightHandAttack, EHitPosition::LeftArm);

	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Idle, nullptr);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Wood__RightHandAttack, RightHandCollision);
}