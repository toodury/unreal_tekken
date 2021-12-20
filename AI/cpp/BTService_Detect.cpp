// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/BTService_Detect.h"
#include "../header/CharacterAIController.h"
#include "../../Character/header/MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// AI 캐릭터
	APawn* ComputerCharacter = Cast<ACharacterAIController>(OwnerComp.GetAIOwner())->GetPawn();
	if (nullptr == ComputerCharacter)
		return;

	UWorld* World = ComputerCharacter->GetWorld();
	FVector Center = ComputerCharacter->GetActorLocation();
	float DetectRadius = 10000.0f;	// 맵 안에 있다면 무조건 탐지 가능하도록 큰 숫자 설정
	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ComputerCharacter);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController())
			{
				Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->SetValueAsObject(ACharacterAIController::Target, PlayerCharacter);
			}
		}
	}
	else
	{
		Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent())->SetValueAsObject(ACharacterAIController::Target, nullptr);
	}
}