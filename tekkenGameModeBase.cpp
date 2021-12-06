// Copyright Epic Games, Inc. All Rights Reserved.


#include "tekkenGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"

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
	return Characters[CharacterToSpawn];
}

/*APawn* AtekkenGameModeBase::SpawnCharacter(ECharacters CharacterToSpawn, FTransform CharacterSpawnTransform)
{
	const TSubclassOf<APawn> SpawnClass = Characters[CharacterToSpawn];
	//GetWorld()->SpawnActor(Characters[CharacterToSpawn], NAME_None, CharacterSpawnTransform.GetLocation(), CharacterSpawnTransform.GetRotation());
	//GetWorld()->SpawnActor<SpawnClass>(CharacterSpawnTransform.GetLocation(), CharacterSpawnTransform.GetRotation().Rotator());
	AMyCharacter* SpawnedCharacter = Cast<SpawnClass>(GetWorld()->SpawnActor<SpawnClass>(CharacterSpawnTransform.GetLocation(), CharacterSpawnTransform.GetRotation().Rotator()));
	return SpawnedCharacter;
}*/

void AtekkenGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidget)
{
	ClearWidget();
	AddWidget(NewWidget);
}

void AtekkenGameModeBase::ClearWidget()
{
	for (int32 i = 0; i < CurrentWidgets.Num(); i++)
	{
		if (CurrentWidgets[i] != nullptr)
			CurrentWidgets[i]->RemoveFromViewport();
	}
	CurrentWidgets = {};
}

void AtekkenGameModeBase::AddWidget(TSubclassOf<UUserWidget> NewWidget)
{
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
	UGameplayStatics::OpenLevel(GetWorld(), FName(*TransferLevelName));
}
