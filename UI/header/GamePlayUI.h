// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "tekkenGameModeBase.h"
#include "GamePlayUI.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UGamePlayUI : public UUserWidget
{
	GENERATED_BODY()

public:

		// 생성자
		virtual void NativeConstruct() override;

		void Tick(FGeometry MyGeometry, float DeltaTime);
		//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
		
		// 이 위젯 내부에서 쓰일 로컬 변수들

		// 게임 모드
		UPROPERTY()
			AtekkenGameModeBase* GameMode;

		// 게임 인스턴스
		UPROPERTY()
			UMyGameInstance* GameInstance;

		// 플레이어 캐릭터
		UPROPERTY()
			AMyCharacter* PlayerCharacter;

		// 컴퓨터 캐릭터
		UPROPERTY()
			AMyCharacter* ComputerCharacter;



		// 게임 결과를 처리하는 변수, 함수들

		// 게임이 종료될 경우 true로 설정. true일 때만 Win Cnt를 1 더함
		UPROPERTY()
			bool bGameOver;

		// true일 경우 다음 레벨로 이동
		UPROPERTY()
			bool bGoToNextLevel;

		// true일 경우 게임 종료
		UPROPERTY()
			bool bQuitGame;

		// 플레이어가 이겼을 때 실행될 함수
		UFUNCTION()
			void WhenPlayerWin();

		// 컴퓨터가 이겼을 때 실행될 함수
		UFUNCTION()
			void WhenComputerWin();

		// 비겼을 때 실행될 함수
		UFUNCTION()
			void WhenDraw();

		// 게임이 끝났을 때 실행될 함수
		UFUNCTION()
			void WhenGameOver();


	
		// 바인딩될 UI 위젯 항목들과 관련 변수, 함수들

		// 1. 캐릭터 체력

		// 플레이어 체력 Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* PlayerHp;

		// 컴퓨터 체력 Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* ComputerHp;

		// 캐릭터 체력 Progress Bar 관련 초기화 함수
		UFUNCTION()
			void InitializeCharacterHpProgressBar();

		// 선택된 캐릭터의 체력 Progress Bar를 업데이트 하는 함수. 체력바의 Percent 값을 리턴
		UFUNCTION()
			float UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar);
			//void UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar);

		// 플레이어 캐릭터의 체력 Progress Bar를 업데이트 하는 함수. 체력바의 Percent 값을 리턴
		UFUNCTION(BlueprintCallable, Category = "Hp")
			float UpdatePlayerHpProgressBar();

		// 컴퓨터 캐릭터의 체력 Progress Bar를 업데이트 하는 함수. 체력바의 Percent 값을 리턴
		UFUNCTION(BlueprintCallable, Category = "Hp")
			float UpdateComputerHpProgressBar();



		// 2. 캐릭터 닉네임

		// 플레이어 닉네임 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* PlayerNicknameText;

		// 컴퓨터 닉네임 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* ComputerNicknameText;

		// 플레이어와 컴퓨터 캐릭터의 닉네임 관련 초기화하는 함수
		UFUNCTION()
			void InitializeNicknameText();



		// 3. 캐릭터별 세트 승리 수를 표시하는 Border, Image
		// N번의 이미지는 해당 캐릭터가 N번의 세트를 승리했을 때 빨간색으로 설정

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

		// 플레이어와 컴퓨터 캐릭터의 세트 승리 수 관련 초기화하는 함수
		UFUNCTION()
			void InitializePlayerAndComputerWins();

		// 플레이어와 컴퓨터 캐릭터의 세트 승리 수를 업데이트하는 함수
		UFUNCTION()
			void UpdatePlayerAndComputerWins();



		// 4. 게임의 남은 시간

		// 게임 진행 60초 중 남은 시간을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* GameCountdownText;

		// 게임 진행 시간 관련 초기화 함수
		UFUNCTION()
			void InitializeGameCountdownText();

		// 게임의 남은 시간을 업데이트 하는 함수. 남은 시간 값을 리턴
		UFUNCTION(BlueprintCallable, Category = "Countdown")
			FText UpdateGameCountdownText();
		/*UFUNCTION()
			void UpdateGameCountdownText();*/



		// 5. 게임 시작 전 3초 대기 시간

		// 게임 시작 전 3초 대기 시간 중 남은 시간을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* CountdownBeforeGameText;

		// 게임 시작 전 대기 시간 관련 초기화 함수
		UFUNCTION()
			void InitializeCountdownBeforeGameText();

		// 게임이 시작했는지 여부를 의미하는 bool 변수
		UPROPERTY()
			bool bGameStart;

		// 게임 시작을 의미하는 함수. UpdateCountdownBerforeGameText 함수에서 실행
		UFUNCTION()
			void GameStart();

		// 게임 시작 전 3초 대기 시간을 업데이트하는 함수. bGameStart = false일 때만 남은 시간 리턴
		UFUNCTION(BlueprintCallable, Category = "Countdown")
			FText UpdateCountdownBeforeGameText();
		/*UFUNCTION()
			void UpdateCountdownBeforeGameText();*/

		// 게임이 끝나고 3초 동안 대기할 타이머가 실행됐는지를 의미하는 bool 변수
		UPROPERTY()
			bool bAfterEndTimerStarted;



		// 6. 누가 이겼는지 결과

		// 누가 이겼는지 결과를 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* WinnerText;

		// WinnerText 관련 초기화하는 함수
		UFUNCTION()
			void InitializeWinnerText();

		// 60초 시간 초과 시 누가 이겼는지 판단하는 함수. UpdateGameCountdownText 함수에서 실행
		UFUNCTION()
			void DetermineWhoWin();



		// 7. 현재 레벨

		// 현재 레벨을 나타내는 텍스트
		UPROPERTY(meta = (BindWidget))
			UTextBlock* LevelText;

		// 현재 레벨 관련 초기화하는 함수
		UFUNCTION()
			void InitializeLevelText();
};
