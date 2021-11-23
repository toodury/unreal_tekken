// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName ACharacterAIController::Target(TEXT("Target"));

ACharacterAIController::ACharacterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_AICharacter.BB_AICharacter"));
	if (BBObject.Succeeded())
	{
		BB_AICharacter = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_AICharacter.BT_AICharacter"));
	if (BTObject.Succeeded())
	{
		BT_AICharacter = BTObject.Object;
	}

	//RepeatInterval = 3.0f;

	RunBehaviorTree(BT_AICharacter);
}

//void ACharacterAIController::OnPossess(APawn* InPawn)
//{
//	Super::OnPossess(InPawn);
//	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &ACharacterAIController::OnRepeatTimer, RepeatInterval, true);
//}
//
//void ACharacterAIController::OnUnPossess()
//{
//	Super::OnUnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//}
//
//void ACharacterAIController::OnRepeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	if (nullptr == CurrentPawn)
//		return;
//
//	//UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	//if (nullptr == NavSystem)
//	//	return;
//	
//	FNavLocation NextLocation;
//
//	//if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
//	//{
//	//	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation);
//	//}
//}