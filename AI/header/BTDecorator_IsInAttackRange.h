// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UBTDecorator_IsInAttackRange : public UBTDecorator
{
    GENERATED_BODY()

public:
    UBTDecorator_IsInAttackRange();

protected:
    // 상대 캐릭터가 최대 공격 범위 안에 있는지 리턴
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
