// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// AI 캐릭터가 공격한 이후 상대 캐릭터를 향해 회전
	UBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
