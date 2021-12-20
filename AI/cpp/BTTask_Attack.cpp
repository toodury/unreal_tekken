// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/BTTask_Attack.h"
#include "../../Character/header/MyCharacter.h"
#include "../header/CharacterAIController.h"

bool UBTTask_Attack::IsAttacking = false;

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI 캐릭터
	auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
	if (nullptr == ComputerCharacter)
		return EBTNodeResult::Failed;

	// 현재 공격 상태를 true로 설정
	IsAttacking = true;

	// 랜덤 공격
	ComputerCharacter->RandomAttack();

	// 공격 이후 0.5초 후에 루트 노드로 복귀
	// 콤보 공격을 위해선 공격 키를 0.7초 안에 입력해야 하므로 0.5초로 설정
	GetWorld()->GetTimerManager().SetTimer(StopAttackTimerHandle, this, &UBTTask_Attack::StopAttack, 0.5f, true);

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
		if (ComputerCharacter != nullptr && !(ComputerCharacter->bAttacking))
		{
			// 캐릭터가 공격 중이지 않을 때
			// 캐릭터를 Idle 상태로 만들고 비헤이비어 트리의 루트 노드로 복귀
			ComputerCharacter->MakeIdle();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

void UBTTask_Attack::StopAttack()
{
	// 현재 공격 상태를 false로 설정해 TickTask 함수에서 비헤이비어 트리의 루트 노드로 복귀
	GetWorld()->GetTimerManager().ClearTimer(StopAttackTimerHandle);
	IsAttacking = false;
}