// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/AnimMyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimMyCharacter::UAnimMyCharacter()
{
	// 각종 변수 초기화
	Speed = 0.0f;
	bIsFalling = false;
	bIsRunning = false;
	bIsHit = false;
	bIsDead = false;
}

void UAnimMyCharacter::NativeBeginPlay()
{
	// 해당 애니메이션이 적용될 캐릭터 가져오기
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Character = Cast<AMyCharacter>(Pawn);
	}
}

void UAnimMyCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character != nullptr)
	{
		// 캐릭터의 이동 속도 -> 캐릭터 이동 애니메이션에 이용
		Speed = Character->GetVelocity().Size();

		// 캐릭터가 공중에 있는지 여부 -> 캐릭터 점프 애니메이션에 이용
		bIsFalling = Character->GetCharacterMovement()->IsFalling();

		// 캐릭터가 뛰고 있는지 여부 -> 캐릭터 달리기 애니메이션에 이용
		bIsRunning = Character->bRunning;

		// 캐릭터가 현재 움직이고 있는 방향 -> 캐릭터 이동 애니메이션에 이용
		MoveDirection = Character->MoveDirection;

		// 캐릭터가 이전에 움직였던 방향 -> 캐릭터 달리기 애니메이션에 이용
		PreviousMovingDirection = Character->PreviousMovingDirection;

		// 캐릭터가 가격 당했는지 여부 -> 캐릭터 Hit 애니메이션에 이용
		bIsHit = Character->bIsHit;

		// 캐릭터가 죽었는지 여부 -> 캐릭터 죽음 애니메이션에 이용
		bIsDead = Character->bIsDead;
	}
}

bool UAnimMyCharacter::GetAttackMotionBoolTable(EAttackMotion AttackMotion) const
{
	if (Character != nullptr)
	{
		// 캐릭터 클래스의 함수 이용
		return Character->GetAttackMotionBoolTable(AttackMotion);
	}
	else
	{
		UE_LOG(LogAnimation, Error, TEXT("Character is nullptr"));
		return false;
	}
}

bool UAnimMyCharacter::GetHitPositionBoolTable(EHitPosition HitPosition) const
{
	if (Character != nullptr)
	{
		// 캐릭터 클래스의 함수 이용
		return Character->GetHitPositionBoolTable(HitPosition);
	}
	else
	{
		UE_LOG(LogAnimation, Error, TEXT("Character is nullptr"));
		return false;
	}
}