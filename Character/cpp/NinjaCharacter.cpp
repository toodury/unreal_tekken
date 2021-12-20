// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacter.h"

ANinjaCharacter::ANinjaCharacter()
{
	// 닌자 캐릭터의 좌우 손발 뼈 이름 설정
	LeftHandSocketName = FName(TEXT("hand_l"));
	RightHandSocketName = FName(TEXT("hand_r"));
	LeftFootSocketName = FName(TEXT("foot_l"));
	RightFootSocketName = FName(TEXT("foot_r"));

	// Character Detail 변수 초기화
	InitializeCharacterDetail();

	// Attack Table 초기화
	InitializeAttackTable();

	// Hit Table 초기화
	InitializeHitTable();

	// 각 캐릭터 클래스 생성자에서 필수적으로 실행해야 할 함수 모음
	CharacterClassCommonConstructor();
}

void ANinjaCharacter::InitializeCharacterDetail()
{
	CharacterID = ECharacters::Ninja;
	CharacterName = FName(TEXT("Ninja"));
	MaxAttackRange = 210;
	MinAttackRange = 120;
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

	/*AttackMotionTable.Emplace(TEXT("H"), TEXT("Left Jap"));
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
	AttackMotionDamageTable.Emplace(TEXT("Wheel Kick"), 20.0f);*/

	AttackMotionTable.Emplace(TEXT("H"), EAttackMotion::Ninja__LeftJap);
	AttackMotionTable.Emplace(TEXT("HH"), EAttackMotion::Ninja__LeftHook);
	AttackMotionTable.Emplace(TEXT("HHH"), EAttackMotion::Ninja__SpinningBackfist);
	AttackMotionTable.Emplace(TEXT("J"), EAttackMotion::Ninja__RightCross);
	AttackMotionTable.Emplace(TEXT("JJ"), EAttackMotion::Ninja__RightUppercut);
	AttackMotionTable.Emplace(TEXT("K"), EAttackMotion::Ninja__ObliqueKick);
	AttackMotionTable.Emplace(TEXT("KK"), EAttackMotion::Ninja__StraightKick);
	AttackMotionTable.Emplace(TEXT("L"), EAttackMotion::Ninja__LowRightThaiKick);
	AttackMotionTable.Emplace(TEXT("LL"), EAttackMotion::Ninja__CutDownKick);
	AttackMotionTable.Emplace(TEXT("KL"), EAttackMotion::Ninja__WheelKick);

	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__LeftJap, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__LeftHook, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__SpinningBackfist, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__RightCross, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__RightUppercut, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__ObliqueKick, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__StraightKick, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__LowRightThaiKick, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__CutDownKick, false);
	AttackMotionBoolTable.Emplace(EAttackMotion::Ninja__WheelKick, false);

	FinalAttackMotions.Emplace(EAttackMotion::Ninja__SpinningBackfist);
	FinalAttackMotions.Emplace(EAttackMotion::Ninja__RightUppercut);
	FinalAttackMotions.Emplace(EAttackMotion::Ninja__StraightKick);
	FinalAttackMotions.Emplace(EAttackMotion::Ninja__CutDownKick);
	FinalAttackMotions.Emplace(EAttackMotion::Ninja__WheelKick);

	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__LeftJap, 5.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__LeftHook, 10.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__SpinningBackfist, 20.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__RightCross, 10.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__RightUppercut, 20.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__ObliqueKick, 5.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__StraightKick, 10.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__LowRightThaiKick, 5.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__CutDownKick, 20.0f);
	AttackMotionDamageTable.Emplace(EAttackMotion::Ninja__WheelKick, 20.0f);
}

void ANinjaCharacter::InitializeHitTable()
{
	AMyCharacter::InitializeHitTable();

	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__LeftJap, EHitPosition::RightArm);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__LeftHook, EHitPosition::RightArm);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__SpinningBackfist, EHitPosition::LeftArm);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__RightCross, EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__RightUppercut, EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__ObliqueKick, EHitPosition::RightLeg);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__StraightKick, EHitPosition::Stomach);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__LowRightThaiKick, EHitPosition::LeftLeg);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__CutDownKick, EHitPosition::Head);
	AttackMotionHitPositionTable.Emplace(EAttackMotion::Ninja__WheelKick, EHitPosition::Head);

	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Idle, nullptr);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__LeftJap, LeftHandCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__LeftHook, LeftHandCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__SpinningBackfist, LeftHandCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__RightCross, RightHandCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__RightUppercut, RightHandCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__ObliqueKick, LeftFootCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__StraightKick, RightFootCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__LowRightThaiKick, RightFootCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__CutDownKick, RightFootCollision);
	AttackMotionCollisionComponentTable.Emplace(EAttackMotion::Ninja__WheelKick, RightFootCollision);
	
}