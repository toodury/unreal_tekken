// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodCharacter.h"

AWoodCharacter::AWoodCharacter()
{
	// 나무 캐릭터의 오른손 뼈 이름 설정
	// 나머지 왼손, 왼발, 오른발은 블루프린트에서 삭제
	RightHandSocketName = FName(TEXT("Bone004"));

	// Character Detail 변수 초기화
	InitializeCharacterDetail();

	// Attack Table 초기화
	InitializeAttackTable();

	// Hit Table 초기화
	InitializeHitTable();

	// 각 캐릭터 클래스 생성자에서 필수적으로 실행해야 할 함수 모음
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