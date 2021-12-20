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
	// AI ĳ���Ͱ� �����ϰ� �ִ��� ������ bool ����
		static bool IsAttacking;

	// AI ĳ���Ͱ� �������� ������ Attack ��忡�� ��� �� �ְ� �ϱ� ���� Ÿ�̸�
		FTimerHandle StopAttackTimerHandle;
	// 2�� ���� Attack ��带 ����� ���� �� ȣ��Ǵ� �Լ�
		void StopAttack();

};
