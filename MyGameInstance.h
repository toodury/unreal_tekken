// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Countdown.h"
#include "CharacterEnumClasses.h"
#include "MyCharacter.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UMyGameInstance();

	// 유저가 캐릭터 선택 화면에서 고른 캐릭터
	UPROPERTY()
		ECharacters PlayerCharacterSelected;

	// 플레이어 캐릭터
	UPROPERTY()
		AMyCharacter* PlayerCharacter;

	// 컴퓨터 캐릭터
	UPROPERTY()
		AMyCharacter* ComputerCharacter;

	// 플레이어 닉네임
	UPROPERTY()
		FString PlayerNickname;

	// 플레이어 세트 승리 횟수
	UPROPERTY()
		int8 PlayerWinCnt;

	// 컴퓨터 세트 승리 횟수
	UPROPERTY()
		int8 ComputerWinCnt;

	// 최고 레벨
	UPROPERTY()
		int8 MaxLevel;

	// 현재 레벨
	UPROPERTY()
		int8 CurrentLevel;

	// 시간을 재기 위한 Countdown 액터
	UPROPERTY()
		ACountdown* CountdownActor;
};
