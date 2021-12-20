// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimMyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimMyCharacter::UAnimMyCharacter()
{
	Speed = 0.0f;
	bIsFalling = false;
	bIsRunning = false;
	bIsHit = false;
	bIsDead = false;
}

void UAnimMyCharacter::NativeBeginPlay()
{
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Character = Cast<AMyCharacter>(Pawn);
	}
	//if (NinjaCharacter != nullptr)
	//{
	//	for (auto Elem : NinjaCharacter->AttackMotionBoolTable)
	//	{
	//		AttackMotionBoolTable.Emplace(Elem.Key, false);
	//	}
	//}
}

void UAnimMyCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character != nullptr)
	{
		Speed = Character->GetVelocity().Size();
		bIsFalling = Character->GetCharacterMovement()->IsFalling();
		bIsRunning = Character->bRunning;
		MoveDirection = Character->MoveDirection;
		PreviousMovingDirection = Character->PreviousMovingDirection;
		bIsHit = Character->bIsHit;
		bIsDead = Character->bIsDead;
		//for (auto Elem : NinjaCharacter->AttackMotionBoolTable)
		//{
		//	AttackMotionBoolTable[Elem.Key] = Elem.Value;
		//}
	}
}

//bool UAnimMyCharacter::GetAttackMotionBoolTable(FString AttackMotion) const
bool UAnimMyCharacter::GetAttackMotionBoolTable(EAttackMotion AttackMotion) const
{
	//if (AttackMotionBoolTable.Contains(AttackMotion))
	//{
	//	return AttackMotionBoolTable[AttackMotion];
	//}
	//else
	//{
	//	UE_LOG(LogAnimation, Error, TEXT("Attack Motion is not contained"));
	//	return false;
	//}
	if (Character != nullptr)
	{
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
		return Character->GetHitPositionBoolTable(HitPosition);
	}
	else
	{
		UE_LOG(LogAnimation, Error, TEXT("Character is nullptr"));
		return false;
	}
}