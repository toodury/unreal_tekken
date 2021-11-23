// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MyCharacter.h"
#include "CharacterAIController.h"

bool UBTTask_Attack::IsAttacking = false;

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
	if (nullptr == ComputerCharacter)
		return EBTNodeResult::Failed;

	IsAttacking = true;

	ComputerCharacter->RandomAttack();

	GetWorld()->GetTimerManager().SetTimer(StopAttackTimerHandle, this, &UBTTask_Attack::StopAttack, 2.0f, true);

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Attack::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(StopAttackTimerHandle);
	IsAttacking = false;
}