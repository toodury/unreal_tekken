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
	
		// �÷��̾� ü�� Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* PlayerHp;

		// ��ǻ�� ü�� Progress Bar
		UPROPERTY(meta = (BindWidget))
			UProgressBar* ComputerHp;

		// �÷��̾� �г��� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* PlayerNicknameText;

		// ��ǻ�� �г��� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* ComputerNicknameText;

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

		// 60�� �� ���� �ð��� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* GameCountdownText;

		// ���� �̰���� ����� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* WinnerText;

		// ���� ���� �� 3�� ��� �ð� �� ���� �ð��� ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* BeforeGameCountdownText;

		// ���� ������ ��Ÿ���� �ؽ�Ʈ
		UPROPERTY(meta = (BindWidget))
			UTextBlock* LevelText;
};
