// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/BTDecorator_IsInAttackRange.h"
#include "../../Character/header/MyCharacter.h"
#include "../header/CharacterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// AI ĳ����
	auto ComputerCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ComputerCharacter)
		return false;

	// ��� ĳ����
	auto PlayerCharacter = Cast<AMyCharacter>(Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->GetValueAsObject(ACharacterAIController::Target));
	if (nullptr == PlayerCharacter)
		return false;

	// ��밡 �ִ� ���� ���� ���� ������ true ����
	// ���� ���� ĳ���Ͱ� �����ϰ� �ְų� ���ݴ��� ���°ų� �׾��ٸ� true�� ������ �������� ���ϵ��� ����
	bResult = (PlayerCharacter->GetDistanceTo(ComputerCharacter) <= ComputerCharacter->MaxAttackRange)
		|| ComputerCharacter->bAttacking || ComputerCharacter->bIsHit || ComputerCharacter->bIsDead;
		//&& PlayerCharacter->GetDistanceTo(ComputerCharacter) >= ComputerCharacter->MinAttackRange);

	// �ִ� ���� ������ �˱� ���� ��� ĳ���Ϳ��� �Ÿ� ���
	UE_LOG(LogTemp, Log, TEXT("%f"), PlayerCharacter->GetDistanceTo(ComputerCharacter));

	return bResult;
}