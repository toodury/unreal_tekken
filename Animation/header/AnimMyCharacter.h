// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Character/header/MyCharacter.h"
#include "AnimMyCharacter.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class TEKKEN_API UAnimMyCharacter : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	// 캐릭터들의 애니메이션 블루프린트 스테이트 머신에서 사용할 bool 변수를 설정하는 클래스
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

	// 캐릭터의 현재 공격 모션을 리턴하는 함수
	// 애니메이션 블루프린트 스테이트 머신에서 애니메이션 전환에 이용하기 위해 순수 함수로 선언
	UFUNCTION(BlueprintCallable, Category = "Attack", meta = (BlueprintThreadSafe))
		bool GetAttackMotionBoolTable(EAttackMotion AttackMotion) const;

	// 캐릭터가 공격 당했을 때 true가 되는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Hit")
		bool bIsHit;

	// 캐릭터가 공격당한 부위를 리턴하는 함수
	// 애니메이션 블루프린트 스테이트 머신에서 애니메이션 전환에 이용하기 위해 순수 함수로 선언
	UFUNCTION(BlueprintCallable, Category = "Hit", meta = (BlueprintThreadSafe))
		bool GetHitPositionBoolTable(EHitPosition HitPosition) const;

	// 캐릭터가 죽었는지를 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Hit")
		bool bIsDead;
};
