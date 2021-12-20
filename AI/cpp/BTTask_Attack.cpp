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

	// AI ĳ����
	auto ComputerCharacter = Cast<AMyCharacter>(Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn());
	if (nullptr == ComputerCharacter)
		return EBTNodeResult::Failed;

	// ���� ���� ���¸� true�� ����
	IsAttacking = true;

	// ���� ����
	ComputerCharacter->RandomAttack();

	// ���� ���� 0.5�� �Ŀ� ��Ʈ ���� ����
	// �޺� ������ ���ؼ� ���� Ű�� 0.7�� �ȿ� �Է��ؾ� �ϹǷ� 0.5�ʷ� ����
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
			// ĳ���Ͱ� ���� ������ ���� ��
			// ĳ���͸� Idle ���·� ����� �����̺�� Ʈ���� ��Ʈ ���� ����
			ComputerCharacter->MakeIdle();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

void UBTTask_Attack::StopAttack()
{
	// ���� ���� ���¸� false�� ������ TickTask �Լ����� �����̺�� Ʈ���� ��Ʈ ���� ����
	GetWorld()->GetTimerManager().ClearTimer(StopAttackTimerHandle);
	IsAttacking = false;
}