// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "MyCharacter.h"
#include "CharacterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ComputerCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ComputerCharacter)
		return false;

	auto PlayerCharacter = Cast<AMyCharacter>(Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->GetValueAsObject(ACharacterAIController::Target));
	if (nullptr == PlayerCharacter)
		return false;

	bResult = (PlayerCharacter->GetDistanceTo(ComputerCharacter) <= ComputerCharacter->MaxAttackRange
		&& PlayerCharacter->GetDistanceTo(ComputerCharacter) >= ComputerCharacter->MinAttackRange);

	UE_LOG(LogTemp, Log, TEXT("%f"), PlayerCharacter->GetDistanceTo(ComputerCharacter));

	return bResult;
}