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

	// AI 캐릭터
	auto ComputerCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ComputerCharacter)
		return false;

	// 상대 캐릭터
	auto PlayerCharacter = Cast<AMyCharacter>(Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->GetValueAsObject(ACharacterAIController::Target));
	if (nullptr == PlayerCharacter)
		return false;

	// 상대가 최대 공격 범위 내에 있으면 true 리턴
	// 만약 현재 캐릭터가 공격하고 있거나 가격당한 상태거나 죽었다면 true를 리턴해 움직이지 못하도록 만듦
	bResult = (PlayerCharacter->GetDistanceTo(ComputerCharacter) <= ComputerCharacter->MaxAttackRange)
		|| ComputerCharacter->bAttacking || ComputerCharacter->bIsHit || ComputerCharacter->bIsDead;
		//&& PlayerCharacter->GetDistanceTo(ComputerCharacter) >= ComputerCharacter->MinAttackRange);

	// 최대 공격 범위를 알기 위해 상대 캐릭터와의 거리 출력
	UE_LOG(LogTemp, Log, TEXT("%f"), PlayerCharacter->GetDistanceTo(ComputerCharacter));

	return bResult;
}