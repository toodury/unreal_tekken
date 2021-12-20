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

	// AI ĳ����
	auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
	if (nullptr == ComputerCharacter)
		return EBTNodeResult::Failed;

	// ��� ĳ����
	auto PlayerCharacter = Cast<AMyCharacter>(Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->GetValueAsObject(ACharacterAIController::Target));
	if (nullptr == PlayerCharacter)
		return EBTNodeResult::Failed;

	// AI ĳ���Ͱ� ��� ĳ���͸� �ٶ󺸴� ���� ���
	FVector LookVector = PlayerCharacter->GetActorLocation() - ComputerCharacter->GetActorLocation();
	LookVector.Z = 0.0f;

	// AI ĳ���Ͱ� ��� ĳ���͸� �ٶ󺸴� ������ ���� 2�� ���� ������ ȸ��
	FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ComputerCharacter->SetActorRotation(FMath::RInterpTo(ComputerCharacter->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.0f));
	
	return EBTNodeResult::Succeeded;
}