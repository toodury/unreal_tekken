// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacter.h"
#include "AnimMyCharacter.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class TEKKEN_API UAnimMyCharacter : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UAnimMyCharacter();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// 애니메이션이 적용될 캐릭터
	UPROPERTY()
		AMyCharacter* Character;

	// 캐릭터가 움직이는 속도
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		float Speed;

	// 캐릭터가 점프 중인지를 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		bool bIsFalling;

	// 캐릭터가 뛰고 있는지를 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		bool bIsRunning;

	// 캐릭터가 움직이고 있는 방향
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		EMoveDirection MoveDirection;

	// 캐릭터가 이전에 움직이고 있던 방향
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
		EMoveDirection PreviousMovingDirection;

	//// 캐릭터의 현재 공격 모션을 가진 map
	//UPROPERTY(BlueprintReadOnly, Category = "Attack")
	//	TMap<FString, bool> AttackMotionBoolTable;

	// 캐릭터의 현재 공격 모션을 리턴하는 함수
	UFUNCTION(BlueprintCallable, Category = "Attack", meta = (BlueprintThreadSafe))
		//bool GetAttackMotionBoolTable(FString AttackMotion) const;
		bool GetAttackMotionBoolTable(EAttackMotion AttackMotion) const;

	// 캐릭터가 공격 당했을 때 true가 되는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Hit")
		bool bIsHit;

	// 캐릭터가 공격당한 부위를 리턴하는 함수
	UFUNCTION(BlueprintCallable, Category = "Hit", meta = (BlueprintThreadSafe))
		bool GetHitPositionBoolTable(EHitPosition HitPosition) const;

	// 캐릭터가 죽었는지를 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Hit")
		bool bIsDead;
};
