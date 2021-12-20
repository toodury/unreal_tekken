// Copyright Epic Games, Inc. All Rights Reserved.


#include "../header/tekkenGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "Kismet/GameplayStatics.h"
#include "../header/MyPlayerController.h"

void AtekkenGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 맵 시작시 초기에 표시될 위젯 설정
	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == FString(TEXT("MenuMap")))
	{
		ChangeWidget(StartingWidget);
		PlayerControllerClass = AMyPlayerController::StaticClass();
	}
	else if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) == FString(TEXT("PlayMap")))
	{
		ChangeWidget(GamePlayWidget);
	}
}

TSubclassOf<APawn> AtekkenGameModeBase::GetCharacterClass(ECharacters CharacterToSpawn)
{
	if (Characters.Contains(CharacterToSpawn))
	{
		return Characters[CharacterToSpawn];
	}
	else
	{
		UE_LOG(LogGameMode, Error, TEXT("Since there is no such Character, cannot Spawn it"));
		return nullptr;
	}
}

void AtekkenGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidget)
{
	// 현재 표시된 위젯을 삭제하고 새로운 위젯 추가
	ClearWidget();
	AddWidget(NewWidget);
}

void AtekkenGameModeBase::ClearWidget()
{
	// 현재 표시되어 있는 모든 위젯 뷰포트에서 삭제

	for (int32 i = 0; i < CurrentWidgets.Num(); i++)
	{
		if (CurrentWidgets[i] != nullptr)
			CurrentWidgets[i]->RemoveFromViewport();
	}
	CurrentWidgets = {};
}

void AtekkenGameModeBase::AddWidget(TSubclassOf<UUserWidget> NewWidget)
{
	// 현재 표시되고 있는 위젯 위에 새로운 위젯 추가

	if (NewWidget != nullptr)
	{
		UUserWidget* New = CreateWidget(GetWorld(), NewWidget);
		if (New != nullptr)
		{
			New->AddToViewport();
			CurrentWidgets.Emplace(New);
		}
	}
}

void AtekkenGameModeBase::ChangeLevel(FString TransferLevelName)
{
	// 맵 바꾸기
	UGameplayStatics::OpenLevel(GetWorld(), FName(*TransferLevelName));
}
