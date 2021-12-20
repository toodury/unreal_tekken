// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/CharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName ACharacterAIController::Target(TEXT("Target"));

ACharacterAIController::ACharacterAIController()
{
	// AI ĳ���� ������ ��������
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_AICharacter.BB_AICharacter"));
	if (BBObject.Succeeded())
	{
		BB_AICharacter = BBObject.Object;
	}

	// AI ĳ���� �����̺�� Ʈ�� ��������
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_AICharacter.BT_AICharacter"));
	if (BTObject.Succeeded())
	{
		BT_AICharacter = BTObject.Object;
	}

	// �����̺�� Ʈ�� ����
	RunBehaviorTree(BT_AICharacter);
}