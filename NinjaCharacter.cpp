// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacter.h"

ANinjaCharacter::ANinjaCharacter()
{
	// 닌자 캐릭터의 좌우 손발 뼈 이름 설정
	LeftHandSocketName = FName(TEXT("hand_l"));
	RightHandSocketName = FName(TEXT("hand_r"));
	LeftFootSocketName = FName(TEXT("foot_l"));
	RightFootSocketName = FName(TEXT("foot_r"));

	// 좌우 손발의 Sphere Collision Component를 매쉬에 Attach
	AttachCollisionComponentsToMesh();

	// Character Detail 변수 초기화
	InitializeCharacterDetail();

	// Attack Table 초기화
	InitializeAttackTable();

	// Hit Table 초기화
	InitializeHitTable();
}

void ANinjaCharacter::InitializeCharacterDetail()
{
	CharacterID = ECharacters::Ninja;
	CharacterName = FName(TEXT("Ninja"));
	AttackRange = 250;
}

void ANinjaCharacter::InitializeAttackTable()
{
	/*TArray<EInputKey> AttackMotion;

	AttackMotion.Emplace(EInputKey::LeftPunch);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Left Jap"));
	AttackMotion.Emplace(EInputKey::LeftPunch);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Left Hook"));
	AttackMotion.Emplace(EInputKey::LeftPunch);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Spinning Backfist"));

	AttackMotion.Empty();
	AttackMotion.Emplace(EInputKey::RightPunch);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Right Cross"));
	AttackMotion.Emplace(EInputKey::RightPunch);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Right Uppercut"));

	AttackMotion.Empty();
	AttackMotion.Emplace(EInputKey::LeftKick);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Oblique Kick"));
	AttackMotion.Emplace(EInputKey::LeftKick);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Straight Kick"));

	AttackMotion.Empty();
	AttackMotion.Emplace(EInputKey::RightKick);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Low Right Thai Kick"));
	AttackMotion.Emplace(EInputKey::RightKick);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Cut Down Kick"));

	AttackMotion.Empty();
	AttackMotion.Emplace(EInputKey::LeftKick);
	AttackMotion.Emplace(EInputKey::RightKick);
	AttackMotionTable.Emplace(FEInputKeyArray(AttackMotion), TEXT("Wheel Kick"));*/

	AttackMotionTable.Emplace(TEXT("H"), TEXT("Left Jap"));
	AttackMotionTable.Emplace(TEXT("HH"), TEXT("Left Hook"));
	AttackMotionTable.Emplace(TEXT("HHH"), TEXT("Spinning Backfist"));
	AttackMotionTable.Emplace(TEXT("J"), TEXT("Right Cross"));
	AttackMotionTable.Emplace(TEXT("JJ"), TEXT("Right Uppercut"));
	AttackMotionTable.Emplace(TEXT("K"), TEXT("Oblique Kick"));
	AttackMotionTable.Emplace(TEXT("KK"), TEXT("Straight Kick"));
	AttackMotionTable.Emplace(TEXT("L"), TEXT("Low Right Thai Kick"));
	AttackMotionTable.Emplace(TEXT("LL"), TEXT("Cut Down Kick"));
	AttackMotionTable.Emplace(TEXT("KL"), TEXT("Wheel Kick	"));

	AttackMotionBoolTable.Emplace(TEXT("Left Jap"), false);
	AttackMotionBoolTable.Emplace(TEXT("Left Hook"), false);
	AttackMotionBoolTable.Emplace(TEXT("Spinning Backfist"), false);
	AttackMotionBoolTable.Emplace(TEXT("Right Cross"), false);
	AttackMotionBoolTable.Emplace(TEXT("Right Uppercut"), false);
	AttackMotionBoolTable.Emplace(TEXT("Oblique Kick"), false);
	AttackMotionBoolTable.Emplace(TEXT("Straight Kick"), false);
	AttackMotionBoolTable.Emplace(TEXT("Low Right Thai Kick"), false);
	AttackMotionBoolTable.Emplace(TEXT("Cut Down Kick"), false);
	AttackMotionBoolTable.Emplace(TEXT("Wheel Kick"), false);

	FinalAttackMotions.Emplace(TEXT("Spinning Backfist"));
	FinalAttackMotions.Emplace(TEXT("Right Uppercut"));
	FinalAttackMotions.Emplace(TEXT("Straight Kick"));
	FinalAttackMotions.Emplace(TEXT("Cut Down Kick"));
	FinalAttackMotions.Emplace(TEXT("Wheel Kick"));

	AttackMotionDamageTable.Emplace(TEXT("Left Jap"), 5.0f);
	AttackMotionDamageTable.Emplace(TEXT("Left Hook"), 10.0f);
	AttackMotionDamageTable.Emplace(TEXT("Spinning Backfist"), 20.0f);
	AttackMotionDamageTable.Emplace(TEXT("Right Cross"), 10.0f);
	AttackMotionDamageTable.Emplace(TEXT("Right Uppercut"), 20.0f);
	AttackMotionDamageTable.Emplace(TEXT("Oblique Kick"), 5.0f);
	AttackMotionDamageTable.Emplace(TEXT("Straight Kick"), 10.0f);
	AttackMotionDamageTable.Emplace(TEXT("Low Right Thai Kick"), 5.0f);
	AttackMotionDamageTable.Emplace(TEXT("Cut Down Kick"), 20.0f);
	AttackMotionDamageTable.Emplace(TEXT("Wheel Kick"), 20.0f);
}

void ANinjaCharacter::InitializeHitTable()
{
	AMyCharacter::InitializeHitTable();

	AttackMotionHitPositionTable.Emplace(TEXT("Left Jap"), EHitPosition::RightArm);
	AttackMotionHitPositionTable.Emplace(TEXT("Left Hook"), EHitPosition::RightArm);
	AttackMotionHitPositionTable.Emplace(TEXT("Spinning Backfist"), EHitPosition::LeftArm);
	AttackMotionHitPositionTable.Emplace(TEXT("Right Cross"), EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(TEXT("Right Uppercut"), EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(TEXT("Oblique Kick"), EHitPosition::RightLeg);
	AttackMotionHitPositionTable.Emplace(TEXT("Straight Kick"), EHitPosition::Stomach);
	AttackMotionHitPositionTable.Emplace(TEXT("Low Right Thai Kick"), EHitPosition::LeftLeg);
	AttackMotionHitPositionTable.Emplace(TEXT("Cut Down Kick"), EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(TEXT("Wheel Kick"), EHitPosition::Head);

	AttakMotionCollisionComponentTable.Emplace(TEXT("Left Jap"), LeftHandCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Left Hook"), LeftHandCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Spinning Backfist"), LeftHandCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Right Cross"), RightHandCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Right Uppercut"), RightHandCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Oblique Kick"), LeftFootCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Straight Kick"), RightFootCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Low Right Thai Kick"), RightFootCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Cut Down Kick"), RightFootCollision);
	AttakMotionCollisionComponentTable.Emplace(TEXT("Wheel Kick"), RightFootCollision);
	
}