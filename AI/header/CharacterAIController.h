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
	// AI 캐릭터를 조종하기 위한 컨트롤러
		ACharacterAIController();

		UBlackboardData* BB_AICharacter;
		UBehaviorTree* BT_AICharacter;
		static const FName Target;
};
