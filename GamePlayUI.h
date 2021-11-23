// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "GamePlayUI.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UGamePlayUI : public UUserWidget
{
	GENERATED_BODY()

public:

		UGamePlayUI(const FObjectInitializer& ObjectInitializer);
	
		// 플레이어 체력 Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* PlayerHp;

		// 컴퓨터 체력 Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* ComputerHp;

		// 플레이어 닉네임 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* PlayerNicknameText;

		// 컴퓨터 닉네임 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* ComputerNicknameText;

		// 플레이어 승리 테두리1
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder1;

		// 플레이어 승리 이미지1
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage1;

		// 플레이어 승리 테두리2
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder2;

		// 플레이어 승리 이미지2
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage2;

		// 플레이어 승리 테두리3
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder3;

		// 플레이어 승리 이미지3
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage3;

		// 컴퓨터 승리 테두리1
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder1;

		// 컴퓨터 승리 이미지1
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage1;

		// 컴퓨터 승리 테두리2
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder2;

		// 컴퓨터 승리 이미지2
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage2;

		// 컴퓨터 승리 테두리3
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder3;

		// 컴퓨터 승리 이미지3
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage3;

		// 60초 중 남은 시간을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* GameCountdownText;

		// 누가 이겼는지 결과를 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* WinnerText;

		// 게임 시작 전 3초 대기 시간 중 남은 시간을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* BeforeGameCountdownText;

		// 현재 레벨을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* LevelText;
};
