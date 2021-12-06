// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayUI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGamePlayUI::NativeConstruct()
{
	// ���� ���� �ʱ�ȭ

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		PlayerCharacter = Cast<AMyCharacter>(GameInstance->PlayerCharacter);
		ComputerCharacter = Cast<AMyCharacter>(GameInstance->ComputerCharacter);
	}

	GameMode = Cast<AtekkenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// ĳ���� ü�� Progress Bar ���� �ʱ�ȭ
	InitializeCharacterHpProgressBar();

	// �÷��̾�� ��ǻ�� ĳ������ �г��� �ʱ�ȭ
	InitializeNicknameText();

	// �÷��̾�� ��ǻ���� ��Ʈ �¸� �� �ʱ�ȭ
	InitializePlayerAndComputerWins();

	// ������ ���� �ð� �ʱ�ȭ
	InitializeGameCountdownText();

	// ���� ���� ���� bool ���� �ʱ�ȭ
	bGameStart = false;
	bAfterEndTimerStarted = false;

	// ���� ���� ��� �ð� �ʱ�ȭ
	InitializeCountdownBeforeGameText();

	// WinnerText �ʱ�ȭ
	InitializeWinnerText();

	// ���� ���� �ʱ�ȭ
	InitializeLevelText();
}

/*void UGamePlayUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// �� ĳ������ ü�¹� ������Ʈ
	UpdateHpProgressBar(PlayerCharacter, PlayerHp);
	UpdateHpProgressBar(ComputerCharacter, ComputerHp);

	// ���� ���� �� 3�� ī��Ʈ�ٿ� ������Ʈ. ������ ���۵��� �� ���� �� ��
	if (!bGameStart)
		UpdateCountdownBeforeGameText();

	// ���� ���� ���� Countdown ������ CountdownTimer �Լ����� 60�ʿ��� �ð��� �پ���� ����. GameStart �Լ����� ������Ʈ ����
	UpdateGameCountdownText();

}*/

void UGamePlayUI::Tick(FGeometry MyGeometry, float DeltaTime)
{
	// �� ĳ������ ü�¹� ������Ʈ
	UpdateHpProgressBar(PlayerCharacter, PlayerHp);
	UpdateHpProgressBar(ComputerCharacter, ComputerHp);

	// ���� ���� �� 3�� ī��Ʈ�ٿ� ������Ʈ. ������ ���۵��� �� ���� �� ��
	if (!bGameStart)
		UpdateCountdownBeforeGameText();

	// ���� ���� ���� Countdown ������ CountdownTimer �Լ����� 60�ʿ��� �ð��� �پ���� ����. GameStart �Լ����� ������Ʈ ����
	UpdateGameCountdownText();

	UE_LOG(LogTemp, Log, TEXT("Tick"));
}

void UGamePlayUI::WhenPlayerWin()
{
	if (GameInstance)
	{
		// �÷��̾� ��Ʈ �¸� ���� �ϳ� �ø��� You Win �ؽ�Ʈ�� ���
		GameInstance->PlayerWinCnt++;
		if (WinnerText)
			WinnerText->SetText(FText::FromString(TEXT("You Win")));

		// �÷��̾� ��Ʈ �¸� 3ȸ �޼� ��
		// ������ ������ ������ �����ִٸ� ���� ������ ����
		// ������ �����̾��ٸ� ���� ����
		if (GameInstance->PlayerWinCnt == 3)
		{
			if (GameInstance->MaxLevel > GameInstance->CurrentLevel)
				bGoToNextLevel = true;
			else
				bQuitGame = true;
		}
	}
}

void UGamePlayUI::WhenComputerWin()
{
	if (GameInstance)
	{
		// ��ǻ�� ��Ʈ �¸� ���� �ϳ� �ø��� You Lose �ؽ�Ʈ�� ���
		GameInstance->ComputerWinCnt++;
		if (WinnerText)
			WinnerText->SetText(FText::FromString(TEXT("You Lose")));

		// ��ǻ�� ��Ʈ �¸� 3ȸ �޼� �� ���� ����
		if (GameInstance->ComputerWinCnt == 3)
			bQuitGame = true;
	}
}

void UGamePlayUI::WhenDraw()
{
	// ����� �� �ƹ� �ϵ� �� �Ͼ�� �� ��Ʈ�� �����ϹǷ� Draw �ؽ�Ʈ�� ����ָ� ��
	if (WinnerText)
		WinnerText->SetText(FText::FromString(TEXT("Draw")));
}

void UGamePlayUI::WhenGameOver()
{
	// �� ĳ������ bGameOver�� true�� ������ �� �̻� ĳ������ ü���� ���� �ʵ��� ����
	if (PlayerCharacter)
		PlayerCharacter->bGameOver = true;
	if (ComputerCharacter)
		ComputerCharacter->bGameOver = true;

	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			if (GameInstance->CountdownActor->bGoNextGame)
			{
				// ���� ����
				if (bQuitGame)
					UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
				else if (bGoToNextLevel)
				{
					// ���� ������ �̵� �� ���� �ν��Ͻ����� ��Ʈ �¸� �� �ʱ�ȭ�ϰ� ���� �ϳ� �ø�
					GameInstance->PlayerWinCnt = 0;
					GameInstance->ComputerWinCnt = 0;
					GameInstance->CurrentLevel++;
				}
				// ���� �ٽ� ����
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayMap"));
			}
			else
			{
				if (!bAfterEndTimerStarted)
				{
					// ���� ���� ���� 3�ʰ� ���
					GameInstance->CountdownActor->StartCountdownAfterEnd();
					bAfterEndTimerStarted = true;
				}
			}
		}
	}
}

void UGamePlayUI::InitializeCharacterHpProgressBar()
{
	// �÷��̾�� ü���� ���ʿ��� ���������� �ް� ��ǻ�ʹ� �ݴ�� ����
	// ������ ü�¹ٴ� 100%�� ���ְ� ������ �ϴû�
	if (PlayerHp)
	{
		PlayerHp->BarFillType = EProgressBarFillType::LeftToRight;
		PlayerHp->SetPercent(1.0f);
		PlayerHp->SetFillColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f, 1.0f));
	}

	if (ComputerHp)
	{
		ComputerHp->BarFillType = EProgressBarFillType::RightToLeft;
		ComputerHp->SetPercent(1.0f);
		ComputerHp->SetFillColorAndOpacity(FLinearColor(0.0f, 0.5f, 1.0f, 1.0f));
	}
}

void UGamePlayUI::UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar)
{
	int CurrentHp = Character->CurrentHp;		// �ش� ĳ������ ü��
	if (HpProgressBar)
	{
		if (CurrentHp == 0)
		{
			// �ش� ĳ������ ü���� 0�� �Ǹ� bIsDead = true�� ����
			// �ش� ĳ���Ͱ� �̰��� ���� �Լ�, ���� ���� �Լ� ����
			Character->bIsDead = true;
			if (HpProgressBar == PlayerHp)
				WhenComputerWin();
			else if (HpProgressBar == ComputerHp)
				WhenPlayerWin();
			else
				UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar is invalid"));
			WhenGameOver();
		}
		// Progress Bar�� 0 ~ 1 ������ ������ �����Ƿ� 100���� ����
		HpProgressBar->SetPercent(CurrentHp / 100.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar is nullptr"));
}

/*float UGamePlayUI::UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar)
{
	int CurrentHp = Character->CurrentHp;		// �ش� ĳ������ ü��
	if (HpProgressBar)
	{
		if (CurrentHp == 0)
		{
			// �ش� ĳ������ ü���� 0�� �Ǹ� bIsDead = true�� ����
			// �ش� ĳ���Ͱ� �̰��� ���� �Լ�, ���� ���� �Լ� ����
			Character->bIsDead = true;
			if (HpProgressBar == PlayerHp)
				WhenComputerWin();
			else if (HpProgressBar == ComputerHp)
				WhenPlayerWin();
			else
				UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar Error"));
			WhenGameOver();
		}
		// Progress Bar�� 0 ~ 1 ������ ������ �����Ƿ� 100���� ����
		HpProgressBar->SetPercent(CurrentHp / 100.0f);
	}
	return CurrentHp / 100.0f;
}

float UGamePlayUI::UpdatePlayerHpProgressBar()
{
	return UpdateHpProgressBar(PlayerCharacter, PlayerHp);
}

float UGamePlayUI::UpdateComputerHpProgressBar()
{
	return UpdateHpProgressBar(ComputerCharacter, ComputerHp);
}*/

void UGamePlayUI::InitializeNicknameText()
{
	if (GameInstance)
	{
		// �÷��̾� �г����� ���� �ν��Ͻ����� ������
		if (PlayerNicknameText)
			PlayerNicknameText->SetText(FText::FromString(GameInstance->PlayerNickname));

		// ��ǻ�� �г����� ���� ������ �ش��ϴ� ĳ������ �̸��� CharacterNameMap���� ������
		if (ComputerNicknameText)
			ComputerNicknameText->SetText(FText::FromName(AMyCharacter::CharacterNameMap[static_cast<ECharacters>(GameInstance->CurrentLevel - 1)]));
	}
}

void UGamePlayUI::InitializePlayerAndComputerWins()
{
	// ó���� ��� �Ͼ������ �ʱ�ȭ
	if (PlayerWinImage1)
		PlayerWinImage1->SetColorAndOpacity(FLinearColor(FColor::White));

	if (PlayerWinImage2)
		PlayerWinImage2->SetColorAndOpacity(FLinearColor(FColor::White));

	if (PlayerWinImage3)
		PlayerWinImage3->SetColorAndOpacity(FLinearColor(FColor::White));

	if (ComputerWinImage1)
		ComputerWinImage1->SetColorAndOpacity(FLinearColor(FColor::White));

	if (ComputerWinImage2)
		ComputerWinImage2->SetColorAndOpacity(FLinearColor(FColor::White));

	if (ComputerWinImage3)
		ComputerWinImage3->SetColorAndOpacity(FLinearColor(FColor::White));

	// ���� �ν��Ͻ��� ĳ���ͺ� ��Ʈ �¸� ���� ���� ���������� ����

	if (GameInstance)
	{
		int8 PlayerWinCnt = GameInstance->PlayerWinCnt;
		int8 ComputerWinCnt = GameInstance->ComputerWinCnt;

		// �÷��̾� ��Ʈ �¸� �� ����
		if (PlayerWinCnt >= 1)
		{
			if (PlayerWinImage1)
				PlayerWinImage1->SetColorAndOpacity(FLinearColor(FColor::Red));
		}
		if (PlayerWinCnt >= 2)
		{
			if (PlayerWinImage2)
				PlayerWinImage2->SetColorAndOpacity(FLinearColor(FColor::Red));
		}
		if (PlayerWinCnt >= 3)
		{
			if (PlayerWinImage3)
				PlayerWinImage3->SetColorAndOpacity(FLinearColor(FColor::Red));
		}

		// ��ǻ�� ��Ʈ �¸� �� ����
		if (ComputerWinCnt >= 1)
		{
			if (ComputerWinImage1)
				ComputerWinImage1->SetColorAndOpacity(FLinearColor(FColor::Red));
		}
		if (ComputerWinCnt >= 2)
		{
			if (ComputerWinImage2)
				ComputerWinImage2->SetColorAndOpacity(FLinearColor(FColor::Red));
		}
		if (ComputerWinCnt >= 3)
		{
			if (ComputerWinImage3)
				ComputerWinImage3->SetColorAndOpacity(FLinearColor(FColor::Red));
		}
	}
}

void UGamePlayUI::InitializeGameCountdownText()
{
	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			int8 Countdown = GameInstance->CountdownActor->CountdownTime;
			if (GameCountdownText)
				GameCountdownText->SetText(FText::FromString(FString::FromInt(Countdown)));
		}
	}
}

/*FText UGamePlayUI::UpdateGameCountdownText()
{
	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			// �ð��� Countdown ���Ϳ��� ������
			int32 Countdown = GameInstance->CountdownActor->CountdownTime;
			if (GameCountdownText)
				GameCountdownText->SetText(FText::FromString(FString::FromInt(Countdown)));
			if (Countdown == 0)
			{
				// �ð��� 0�� �Ǹ� ���� ü�¿� ���� ���� �̰���� �����ϰ� ���� ���� �Լ� ����
				DetermineWhoWin();
				WhenGameOver();
			}
			return FText::FromString(FString::FromInt(Countdown));
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Game Instance = nullptr"));
	return FText::FromString(TEXT(""));
}*/

void UGamePlayUI::UpdateGameCountdownText()
{
	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			// �ð��� Countdown ���Ϳ��� ������
			int8 Countdown = GameInstance->CountdownActor->CountdownTime;
			if (GameCountdownText)
				GameCountdownText->SetText(FText::FromString(FString::FromInt(Countdown)));
			if (Countdown == 0)
			{
				// �ð��� 0�� �Ǹ� ���� ü�¿� ���� ���� �̰���� �����ϰ� ���� ���� �Լ� ����
				DetermineWhoWin();
				WhenGameOver();
			}
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Game Instance->Countdown Actor is nullptr"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Game Instance is nullptr"));
}

void UGamePlayUI::InitializeCountdownBeforeGameText()
{
	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			int8 Countdown = GameInstance->CountdownActor->CountdownBeforeStartAfterEnd;
			if (CountdownBeforeGameText)
				CountdownBeforeGameText->SetText(FText::FromString(FString::FromInt(Countdown)));
		}
	}
}

void UGamePlayUI::GameStart()
{
	// ������ ���۵� �� �Ͼ�� �� �ϵ�

	// ���� ���� �� 3�� �ð��� ���ִ� �ؽ�Ʈ�� ��������� ��
	if (CountdownBeforeGameText)
		CountdownBeforeGameText->SetText(FText::FromString(TEXT("")));

	// ������� ��Ʈ�ѷ��� �÷��̾� ĳ���Ϳ��� �Ѱ���
	GetWorld()->GetFirstPlayerController()->Possess(PlayerCharacter);

	// UpdateCountdownBerforeGameText �Լ��� �� �̻� ȣ������ ����
	bGameStart = true;

	// 60�� ī��Ʈ�ٿ� ����
	if (GameInstance)
		GameInstance->CountdownActor->StartCountdownTimer();
}

void UGamePlayUI::UpdateCountdownBeforeGameText()
{
	if (GameInstance)
	{
		if (GameInstance->CountdownActor)
		{
			if (GameInstance->CountdownActor->bStartGame)
				GameStart();
			else
			{
				// ���� ���� ������ �� �� ���Ҵ��� ������
				int8 Countdown = GameInstance->CountdownActor->CountdownBeforeStartAfterEnd;
				if (CountdownBeforeGameText)
				{
					// �ð��� �������� �ð�����, �ð��� 0�� �� ���� 0 ��� Go!�� ����
					if (Countdown > 0)
						CountdownBeforeGameText->SetText(FText::FromString(FString::FromInt(Countdown)));
					else
						CountdownBeforeGameText->SetText(FText::FromString(TEXT("Go!")));
				}
			}
		}
		else
			UE_LOG(LogTemp, Error, TEXT("Game Instance->Countdown Actor is nullptr"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Game Instance is nullptr"));
}

/*FText UGamePlayUI::UpdateCountdownBeforeGameText()
{
	if (!bGameStart)
	{
		if (GameInstance)
		{
			if (GameInstance->CountdownActor)
			{
				if (GameInstance->CountdownActor->bStartGame)
					GameStart();
				else
				{
					// ���� ���� ������ �� �� ���Ҵ��� ������
					int32 Countdown = GameInstance->CountdownActor->CountdownBeforeStartAfterEnd;
					if (CountdownBeforeGameText)
					{
						// �ð��� �������� �ð�����, �ð��� 0�� �� ���� 0 ��� Go!�� ����
						if (Countdown > 0)
							CountdownBeforeGameText->SetText(FText::FromString(FString::FromInt(Countdown)));
						else
							CountdownBeforeGameText->SetText(FText::FromString(TEXT("Go!")));
					}
					return FText::FromString(FString::FromInt(Countdown));
				}
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Game Instance = nullptr"));
	}
	return FText::FromString(TEXT(""));
}*/

void UGamePlayUI::InitializeWinnerText()
{
	if (WinnerText)
		WinnerText->SetText(FText::FromString(TEXT("")));
}

void UGamePlayUI::DetermineWhoWin()
{
	if (GameInstance)
	{
		// �� ĳ������ ���� ü���� �о�ͼ� ���� �̰���� �Ǵ��ϰ�
		// �׿� ���� �¸� �Լ� ����
		int32 ComputerCharacterHp = ComputerCharacter->CurrentHp;
		int32 PlayerCharacterHp = PlayerCharacter->CurrentHp;
		if (ComputerCharacterHp > PlayerCharacterHp)
			WhenComputerWin();
		else if (ComputerCharacterHp < PlayerCharacterHp)
			WhenPlayerWin();
		else
			WhenDraw();
	}
}

void UGamePlayUI::InitializeLevelText()
{
	if (GameInstance)
	{
		int8 CurrentLevel = GameInstance->CurrentLevel;
		if (LevelText)
		{
			LevelText->SetText(FText::FromString(TEXT("Level") + FString::FromInt(CurrentLevel)));
		}
	}
}