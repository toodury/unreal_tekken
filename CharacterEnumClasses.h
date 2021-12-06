// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEnumClasses.generated.h"

// ĳ���Ͱ� �����̰� �ִ� ����
UENUM(BlueprintType)
enum class EMoveDirection : uint8 {
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left")
};

// ������ ���� �Է�Ű 4����
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
//	// AttackMotionTable�� Key�� EInputKey�� �迭�� �ֱ� ���� TArray<EInputKey>�� ���� ���� ����ü
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

// ĳ���Ͱ� ���� �� �ִ� ����
UENUM(BlueprintType)
enum class EHitPosition : uint8 {
	LeftArm UMETA(DisplayName = "LeftArm"),
	RightArm UMETA(DisplayName = "RightArm"),
	LeftLeg UMETA(DisplayName = "LeftLeg"),
	RightLeg UMETA(DisplayName = "RightLeg"),
	Head UMETA(DisplayName = "Head"),
	Stomach UMETA(DisplayName = "Stomach")
};

// �� �������� ������ Random���� ����
UENUM(BlueprintType)
enum class ECharacters : uint8 {
	Wood UMETA(DisplayName = "Wood"),
	Ninja UMETA(DisplayName = "Ninja"),
	Random UMETA(DisplayName = "Random")
};

class TEKKEN_API CharacterEnumClasses
{
		
};
