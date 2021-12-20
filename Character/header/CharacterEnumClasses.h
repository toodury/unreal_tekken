// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEnumClasses.generated.h"

// 캐릭터가 움직이고 있는 방향
UENUM(BlueprintType)
enum class EMoveDirection : uint8 {
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left")
};

// 공격을 위한 입력키 4가지
UENUM(BlueprintType)
enum class EInputKey : uint8 {
	LeftPunch UMETA(DisplayName = "LeftPunch"),
	RightPunch UMETA(DisplayName = "RightPunch"),
	LeftKick UMETA(DisplayName = "LeftKick"),
	RightKick UMETA(DisplayName = "RightKick")
};

//USTRUCT(Atomic)
//struct FEInputKeyArray {
//
//	// AttackMotionTable의 Key로 EInputKey의 배열을 넣기 위해 TArray<EInputKey>를 감싸 만든 구조체
//
//	GENERATED_USTRUCT_BODY()
//
//public:
//UPROPERTY()
//		TArray<EInputKey> EInputKeyArray;
//
//	FEInputKeyArray();
//
//	FEInputKeyArray(TArray<EInputKey> NewEInputKeyArray)
//	{
//		for (int32 i = 0; i < NewEInputKeyArray.Num(); i++)
//			EInputKeyArray.Emplace(NewEInputKeyArray[i]);
//	}
//
//	bool operator==(FEInputKeyArray obj)
//	{
//		if (obj.EInputKeyArray.Num() != EInputKeyArray.Num())
//			return false;
//		for (int32 i = 0; i < obj.EInputKeyArray.Num(); i++)
//		{
//			if (EInputKeyArray[i] != obj.EInputKeyArray[i])
//				return false;
//		}
//		return true;
//	}
//};

// 캐릭터가 맞을 수 있는 부위
UENUM(BlueprintType)
enum class EHitPosition : uint8 {
	LeftArm UMETA(DisplayName = "LeftArm"),
	RightArm UMETA(DisplayName = "RightArm"),
	LeftLeg UMETA(DisplayName = "LeftLeg"),
	RightLeg UMETA(DisplayName = "RightLeg"),
	Head UMETA(DisplayName = "Head"),
	Stomach UMETA(DisplayName = "Stomach")
};

// 맨 마지막은 무조건 Random으로 설정
UENUM(BlueprintType)
enum class ECharacters : uint8 {
	Wood UMETA(DisplayName = "Wood"),
	Ninja UMETA(DisplayName = "Ninja"),
	Random UMETA(DisplayName = "Random")
};

// 모든 캐릭터들의 공격 모션 모음
// 캐릭터이름__공격모션
// 캐릭터의 첫번째 공격 모션이라면 맨뒤에 _Fisrt, 마지막이라면 _Last를 붙여야 함
UENUM(BlueprintType)
enum class EAttackMotion : uint8 {
	Idle UMETA(DisplayName = "Idle"),
	Wood__RightHandAttack UMETA(DisplayName = "Wood__RightHandAttack"),
	Ninja__LeftJap UMETA(DisplayName = "Ninja__LeftJap"),
	Ninja__LeftHook UMETA(DisplayName = "Ninja__LeftHook"),
	Ninja__SpinningBackfist UMETA(DisplayName = "Ninja__SpinningBackfist"),
	Ninja__RightCross UMETA(DisplayName = "Ninja__RightCross"),
	Ninja__RightUppercut UMETA(DisplayName = "Ninja__RightUppercut"),
	Ninja__ObliqueKick UMETA(DisplayName = "Ninja__ObliqueKick"),
	Ninja__StraightKick UMETA(DisplayName = "Ninja__StraightKick"),
	Ninja__LowRightThaiKick UMETA(DisplayName = "Ninja__LowRightThaiKick"),
	Ninja__CutDownKick UMETA(DisplayName = "Ninja__CutDownKick"),
	Ninja__WheelKick UMETA(DisplayName = "Ninja__WheelKick")
};

class TEKKEN_API CharacterEnumClasses
{
		
};
