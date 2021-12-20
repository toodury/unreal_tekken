// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/CharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName ACharacterAIController::Target(TEXT("Target"));

ACharacterAIController::ACharacterAIController()
{
	// AI 캐릭터 블랙보드 가져오기
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_AICharacter.BB_AICharacter"));
	if (BBObject.Succeeded())
	{
		BB_AICharacter = BBObject.Object;
	}

	// AI 캐릭터 비헤이비어 트리 가져오기
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_AICharacter.BT_AICharacter"));
	if (BTObject.Succeeded())
	{
		BT_AICharacter = BTObject.Object;
	}

	// 비헤이비어 트리 실행
	RunBehaviorTree(BT_AICharacter);
}