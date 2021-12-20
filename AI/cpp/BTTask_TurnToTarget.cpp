// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/BTTask_TurnToTarget.h"
#include "../../Character/header/MyCharacter.h"
#include "../header/CharacterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}


EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI 캐릭터
	auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
	if (nullptr == ComputerCharacter)
		return EBTNodeResult::Failed;

	// 상대 캐릭터
	auto PlayerCharacter = Cast<AMyCharacter>(Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->GetValueAsObject(ACharacterAIController::Target));
	if (nullptr == PlayerCharacter)
		return EBTNodeResult::Failed;

	// AI 캐릭터가 상대 캐릭터를 바라보는 방향 계산
	FVector LookVector = PlayerCharacter->GetActorLocation() - ComputerCharacter->GetActorLocation();
	LookVector.Z = 0.0f;

	// AI 캐릭터가 상대 캐릭터를 바라보는 방향을 따라 2초 동안 서서히 회전
	FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ComputerCharacter->SetActorRotation(FMath::RInterpTo(ComputerCharacter->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.0f));
	
	return EBTNodeResult::Succeeded;
}