// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMapLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Countdown.h"

APlayMapLevelScriptActor::APlayMapLevelScriptActor()
{

}

void APlayMapLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();


}

void APlayMapLevelScriptActor::PlayMapBeginPlay()
{
	GameMode = Cast<AtekkenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameMode != nullptr && GameInstance != nullptr)
	{
		// 플레이어 캐릭터 스폰
		ECharacters PlayerCharacterToSpawn = GameInstance->PlayerCharacterSelected;
		FTransform PlayerCharacterSpawnTransform;
		PlayerCharacterSpawnTransform.SetLocation(FVector(0.0f, 0.0f, 0.0f));
		PlayerCharacterSpawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 0.0f)));

		APawn* SpawnedPlayerCharacter;
		GameMode->SpawnCharacter(PlayerCharacterToSpawn, PlayerCharacterSpawnTransform, SpawnedPlayerCharacter);

		GameInstance->PlayerCharacter = Cast<AMyCharacter>(SpawnedPlayerCharacter);
		//GameInstance->PlayerCharacter->bIsControlledByAI = false;

		// 컴퓨터 캐릭터 스폰
		ECharacters ComputerCharacterToSpawn = static_cast<ECharacters>(GameInstance->CurrentLevel - 1);
		FTransform ComputerCharacterSpawnTransform;
		ComputerCharacterSpawnTransform.SetLocation(FVector(496.0f, 10.0f, 92.0f));
		ComputerCharacterSpawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, -180.0f)));

		APawn* SpawnedComputerCharacter;
		GameMode->SpawnCharacter(ComputerCharacterToSpawn, ComputerCharacterSpawnTransform, SpawnedComputerCharacter);

		GameInstance->ComputerCharacter = Cast<AMyCharacter>(SpawnedComputerCharacter);

		// Countdown 액터 스폰
		//ACountdown* Countdown = Cast<ACountdown>(GetWorld()->SpawnActor(ACountdown::StaticClass(), NAME_None, FVector(0.0f, 0.0f, -2000.0f)));
		ACountdown* Countdown = Cast<ACountdown>(GetWorld()->SpawnActor<ACountdown>(FVector(0.0f, 0.0f, -2000.0f), FRotator(0.0f, 0.0f, 0.0f)));
		GameInstance->CountdownActor = Countdown;
		GameInstance->CountdownActor->StartCountdownBeforeStart();
	}
}