// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	// AI 캐릭터가 공격하고 있는지 저장한 bool 변수
		static bool IsAttacking;

	// AI 캐릭터가 랜덤 공격 이후 0.5초 기다리기 위해 있는 타이머 핸들
		FTimerHandle StopAttackTimerHandle;

	// AI 캐릭터가 랜덤 공격 이후 0.5초 후에 실행되는 함수. 비헤이비어 트리의 루트 노드로 돌아감
		void StopAttack();

};
