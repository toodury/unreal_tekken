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

	// AI 캐릭터가 움직이지 않을시 Attack 노드에서 벗어날 수 있게 하기 위한 타이머
		FTimerHandle StopAttackTimerHandle;
	// 2초 동안 Attack 노드를 벗어나지 못할 시 호출되는 함수
		void StopAttack();

};
