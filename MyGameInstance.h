// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Countdown.h"
#include "CharacterEnumClasses.h"
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

	// ������ ĳ���� ���� ȭ�鿡�� ���� ĳ����
	UPROPERTY()
		ECharacters PlayerCharacterSelected;

	// �÷��̾� ĳ����
	UPROPERTY()
		ACharacter* PlayerCharacter;

	// ��ǻ�� ĳ����
	UPROPERTY()
		ACharacter* ComputerCharacter;

	// �÷��̾� �г���
	UPROPERTY()
		FString PlayerNickname;

	// �÷��̾� ��Ʈ �¸� Ƚ��
	UPROPERTY()
		int8 PlayerWinCnt;

	// ��ǻ�� ��Ʈ �¸� Ƚ��
	UPROPERTY()
		int8 ComputerWinCnt;

	// ���� ����
	UPROPERTY()
		int8 Level;

	// �ð��� ��� ���� Countdown ����
	UPROPERTY()
		ACountdown* CountdownActor;
};