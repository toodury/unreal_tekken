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

		// ������
		virtual void NativeConstruct() override;

		void Tick(FGeometry MyGeometry, float DeltaTime);
		//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
		
		// �� ���� ���ο��� ���� ���� ������

		// ���� ���
		UPROPERTY()
			AtekkenGameModeBase* GameMode;

		// ���� �ν��Ͻ�
		UPROPERTY()
			UMyGameInstance* GameInstance;

		// �÷��̾� ĳ����
		UPROPERTY()
			AMyCharacter* PlayerCharacter;

		// ��ǻ�� ĳ����
		UPROPERTY()
			AMyCharacter* ComputerCharacter;



		// ���� ����� ó���ϴ� ����, �Լ���

		// true�� ��� ���� ������ �̵�
		UPROPERTY()
			bool bGoToNextLevel;

		// true�� ��� ���� ����
		UPROPERTY()
			bool bQuitGame;

		// �÷��̾ �̰��� �� ����� �Լ�
		UFUNCTION()
			void WhenPlayerWin();

		// ��ǻ�Ͱ� �̰��� �� ����� �Լ�
		UFUNCTION()
			void WhenComputerWin();

		// ����� �� ����� �Լ�
		UFUNCTION()
			void WhenDraw();

		// ������ ������ �� ����� �Լ�
		UFUNCTION()
			void WhenGameOver();


	
		// ���ε��� UI ���� �׸��� ���� ����, �Լ���

		// 1. ĳ���� ü��

		// �÷��̾� ü�� Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* PlayerHp;

		// ��ǻ�� ü�� Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* ComputerHp;

		// ĳ���� ü�� Progress Bar ���� �ʱ�ȭ �Լ�
		UFUNCTION()
			void InitializeCharacterHpProgressBar();

		// ���õ� ĳ������ ü�� Progress Bar�� ������Ʈ �ϴ� �Լ�. ü�¹��� Percent ���� ����
		UFUNCTION()
			//float UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar);
			void UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar);

		/*// �÷��̾� ĳ������ ü�� Progress Bar�� ������Ʈ �ϴ� �Լ�. ü�¹��� Percent ���� ����
		UFUNCTION(BlueprintCallable, Category = "Hp")
			float UpdatePlayerHpProgressBar();

		// ��ǻ�� ĳ������ ü�� Progress Bar�� ������Ʈ �ϴ� �Լ�. ü�¹��� Percent ���� ����
		UFUNCTION(BlueprintCallable, Category = "Hp")
			float UpdateComputerHpProgressBar();*/



		// 2. ĳ���� �г���

		// �÷��̾� �г��� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* PlayerNicknameText;

		// ��ǻ�� �г��� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* ComputerNicknameText;

		// �÷��̾�� ��ǻ�� ĳ������ �г��� ���� �ʱ�ȭ�ϴ� �Լ�
		UFUNCTION()
			void InitializeNicknameText();



		// 3. ĳ���ͺ� ��Ʈ �¸� ���� ǥ���ϴ� Border, Image
		// N���� �̹����� �ش� ĳ���Ͱ� N���� ��Ʈ�� �¸����� �� ���������� ����

		// �÷��̾� �¸� �׵θ�1
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder1;

		// �÷��̾� �¸� �̹���1
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage1;

		// �÷��̾� �¸� �׵θ�2
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder2;

		// �÷��̾� �¸� �̹���2
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage2;

		// �÷��̾� �¸� �׵θ�3
		UPROPERTY(meta = (BindWidget))
			UBorder* PlayerWinBorder3;

		// �÷��̾� �¸� �̹���3
		UPROPERTY(meta = (BindWidget))
			UImage* PlayerWinImage3;

		// ��ǻ�� �¸� �׵θ�1
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder1;

		// ��ǻ�� �¸� �̹���1
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage1;

		// ��ǻ�� �¸� �׵θ�2
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder2;

		// ��ǻ�� �¸� �̹���2
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage2;

		// ��ǻ�� �¸� �׵θ�3
		UPROPERTY(meta = (BindWidget))
			UBorder* ComputerWinBorder3;

		// ��ǻ�� �¸� �̹���3
		UPROPERTY(meta = (BindWidget))
			UImage* ComputerWinImage3;

		// �÷��̾�� ��ǻ�� ĳ������ ��Ʈ �¸� �� ���� �ʱ�ȭ�ϴ� �Լ�
		UFUNCTION()
			void InitializePlayerAndComputerWins();



		// 4. ������ ���� �ð�

		// ���� ���� 60�� �� ���� �ð��� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* GameCountdownText;

		// ���� ���� �ð� ���� �ʱ�ȭ �Լ�
		UFUNCTION()
			void InitializeGameCountdownText();

		// ������ ���� �ð��� ������Ʈ �ϴ� �Լ�. ���� �ð� ���� ����
		/*UFUNCTION(BlueprintCallable, Category = "Countdown")
			FText UpdateGameCountdownText();*/
		UFUNCTION()
			void UpdateGameCountdownText();



		// 5. ���� ���� �� 3�� ��� �ð�

		// ���� ���� �� 3�� ��� �ð� �� ���� �ð��� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* CountdownBeforeGameText;

		// ���� ���� �� ��� �ð� ���� �ʱ�ȭ �Լ�
		UFUNCTION()
			void InitializeCountdownBeforeGameText();

		// ������ �����ߴ��� ���θ� �ǹ��ϴ� bool ����
		UPROPERTY()
			bool bGameStart;

		// ���� ������ �ǹ��ϴ� �Լ�. UpdateCountdownBerforeGameText �Լ����� ����
		UFUNCTION()
			void GameStart();

		// ���� ���� �� 3�� ��� �ð��� ������Ʈ�ϴ� �Լ�. bGameStart = false�� ���� ���� �ð� ����
		/*UFUNCTION(BlueprintCallable, Category = "Countdown")
			FText UpdateCountdownBeforeGameText();*/
		UFUNCTION()
			void UpdateCountdownBeforeGameText();

		// ������ ������ 3�� ���� ����� Ÿ�̸Ӱ� ����ƴ����� �ǹ��ϴ� bool ����
		UPROPERTY()
			bool bAfterEndTimerStarted;



		// 6. ���� �̰���� ���

		// ���� �̰���� ����� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* WinnerText;

		// WinnerText ���� �ʱ�ȭ�ϴ� �Լ�
		UFUNCTION()
			void InitializeWinnerText();

		// 60�� �ð� �ʰ� �� ���� �̰���� �Ǵ��ϴ� �Լ�. UpdateGameCountdownText �Լ����� ����
		UFUNCTION()
			void DetermineWhoWin();



		// 7. ���� ����

		// ���� ������ ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* LevelText;

		// ���� ���� ���� �ʱ�ȭ�ϴ� �Լ�
		UFUNCTION()
			void InitializeLevelText();
};
