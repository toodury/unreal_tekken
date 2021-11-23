// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
		ACharacterAIController();

		UBlackboardData* BB_AICharacter;
		UBehaviorTree* BT_AICharacter;
		static const FName Target;

//		virtual void OnPossess(APawn* InPawn) override;
//		virtual void OnUnPossess() override;
//
//private:
//	void OnRepeatTimer();
//	FTimerHandle RepeatTimerHandle;
//	float RepeatInterval;
};
