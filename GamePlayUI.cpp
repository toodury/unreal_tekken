// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayUI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGamePlayUI::NativeConstruct()
{
	// 로컬 변수 초기화

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		PlayerCharacter = Cast<AMyCharacter>(GameInstance->PlayerCharacter);
		ComputerCharacter = Cast<AMyCharacter>(GameInstance->ComputerCharacter);
	}

	GameMode = Cast<AtekkenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// 캐릭터 체력 Progress Bar 관련 초기화
	InitializeCharacterHpProgressBar();

	// 플레이어와 컴퓨터 캐릭터의 닉네임 초기화
	InitializeNicknameText();

	// 플레이어와 컴퓨터의 세트 승리 수 초기화
	InitializePlayerAndComputerWins();

	// 게임의 진행 시간 초기화
	InitializeGameCountdownText();

	// 게임 진행 관련 bool 변수 초기화
	bGameStart = false;
	bAfterEndTimerStarted = false;

	// 게임 시작 대기 시간 초기화
	InitializeCountdownBeforeGameText();

	// WinnerText 초기화
	InitializeWinnerText();

	// 현재 레벨 초기화
	InitializeLevelText();
}

/*void UGamePlayUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 두 캐릭터의 체력바 업데이트
	UpdateHpProgressBar(PlayerCharacter, PlayerHp);
	UpdateHpProgressBar(ComputerCharacter, ComputerHp);

	// 게임 시작 전 3초 카운트다운 업데이트. 게임이 시작됐을 땐 실행 안 됨
	if (!bGameStart)
		UpdateCountdownBeforeGameText();

	// 게임 시작 전엔 Countdown 액터의 CountdownTimer 함수에서 60초에서 시간이 줄어들지 않음. GameStart 함수에서 업데이트 시작
	UpdateGameCountdownText();

}*/

void UGamePlayUI::Tick(FGeometry MyGeometry, float DeltaTime)
{
	// 두 캐릭터의 체력바 업데이트
	UpdateHpProgressBar(PlayerCharacter, PlayerHp);
	UpdateHpProgressBar(ComputerCharacter, ComputerHp);

	// 게임 시작 전 3초 카운트다운 업데이트. 게임이 시작됐을 땐 실행 안 됨
	if (!bGameStart)
		UpdateCountdownBeforeGameText();

	// 게임 시작 전엔 Countdown 액터의 CountdownTimer 함수에서 60초에서 시간이 줄어들지 않음. GameStart 함수에서 업데이트 시작
	UpdateGameCountdownText();

	UE_LOG(LogTemp, Log, TEXT("Tick"));
}

void UGamePlayUI::WhenPlayerWin()
{
	if (GameInstance)
	{
		// 플레이어 세트 승리 수를 하나 올리고 You Win 텍스트를 띄움
		GameInstance->PlayerWinCnt++;
		if (WinnerText)
			WinnerText->SetText(FText::FromString(TEXT("You Win")));

		// 플레이어 세트 승리 3회 달성 시
		// 앞으로 진행할 레벨이 남아있다면 다음 레벨로 진행
		// 마지막 레벨이었다면 게임 종료
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
		// 컴퓨터 세트 승리 수를 하나 올리고 You Lose 텍스트를 띄움
		GameInstance->ComputerWinCnt++;
		if (WinnerText)
			WinnerText->SetText(FText::FromString(TEXT("You Lose")));

		// 컴퓨터 세트 승리 3회 달성 시 게임 종료
		if (GameInstance->ComputerWinCnt == 3)
			bQuitGame = true;
	}
}

void UGamePlayUI::WhenDraw()
{
	// 비겼을 시 아무 일도 안 일어나고 새 세트를 시작하므로 Draw 텍스트만 띄워주면 됨
	if (WinnerText)
		WinnerText->SetText(FText::FromString(TEXT("Draw")));
}

void UGamePlayUI::WhenGameOver()
{
	// 각 캐릭터의 bGameOver를 true로 설정해 더 이상 캐릭터의 체력이 달지 않도록 설정
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
				// 게임 종료
				if (bQuitGame)
					UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
				else if (bGoToNextLevel)
				{
					// 다음 레벨로 이동 시 게임 인스턴스에서 세트 승리 수 초기화하고 레벨 하나 올림
					GameInstance->PlayerWinCnt = 0;
					GameInstance->ComputerWinCnt = 0;
					GameInstance->CurrentLevel++;
				}
				// 게임 다시 시작
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayMap"));
			}
			else
			{
				if (!bAfterEndTimerStarted)
				{
					// 게임 종료 이후 3초간 대기
					GameInstance->CountdownActor->StartCountdownAfterEnd();
					bAfterEndTimerStarted = true;
				}
			}
		}
	}
}

void UGamePlayUI::InitializeCharacterHpProgressBar()
{
	// 플레이어는 체력이 왼쪽에서 오른쪽으로 달고 컴퓨터는 반대로 달음
	// 최초의 체력바는 100%로 차있고 색깔은 하늘색
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
	int CurrentHp = Character->CurrentHp;		// 해당 캐릭터의 체력
	if (HpProgressBar)
	{
		if (CurrentHp == 0)
		{
			// 해당 캐릭터의 체력이 0이 되면 bIsDead = true로 설정
			// 해당 캐릭터가 이겼을 때의 함수, 게임 종료 함수 실행
			Character->bIsDead = true;
			if (HpProgressBar == PlayerHp)
				WhenComputerWin();
			else if (HpProgressBar == ComputerHp)
				WhenPlayerWin();
			else
				UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar is invalid"));
			WhenGameOver();
		}
		// Progress Bar는 0 ~ 1 사이의 범위를 가지므로 100으로 나눔
		HpProgressBar->SetPercent(CurrentHp / 100.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar is nullptr"));
}

/*float UGamePlayUI::UpdateHpProgressBar(AMyCharacter* Character, UProgressBar* HpProgressBar)
{
	int CurrentHp = Character->CurrentHp;		// 해당 캐릭터의 체력
	if (HpProgressBar)
	{
		if (CurrentHp == 0)
		{
			// 해당 캐릭터의 체력이 0이 되면 bIsDead = true로 설정
			// 해당 캐릭터가 이겼을 때의 함수, 게임 종료 함수 실행
			Character->bIsDead = true;
			if (HpProgressBar == PlayerHp)
				WhenComputerWin();
			else if (HpProgressBar == ComputerHp)
				WhenPlayerWin();
			else
				UE_LOG(LogTemp, Error, TEXT("Hp Progress Bar Error"));
			WhenGameOver();
		}
		// Progress Bar는 0 ~ 1 사이의 범위를 가지므로 100으로 나눔
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
		// 플레이어 닉네임은 게임 인스턴스에서 가져옴
		if (PlayerNicknameText)
			PlayerNicknameText->SetText(FText::FromString(GameInstance->PlayerNickname));

		// 컴퓨터 닉네임은 현재 레벨에 해당하는 캐릭터의 이름을 CharacterNameMap에서 가져옴
		if (ComputerNicknameText)
			ComputerNicknameText->SetText(FText::FromName(AMyCharacter::CharacterNameMap[static_cast<ECharacters>(GameInstance->CurrentLevel - 1)]));
	}
}

void UGamePlayUI::InitializePlayerAndComputerWins()
{
	// 처음엔 모두 하얀색으로 초기화
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

	// 게임 인스턴스의 캐릭터별 세트 승리 수에 따라 빨간색으로 설정

	if (GameInstance)
	{
		int8 PlayerWinCnt = GameInstance->PlayerWinCnt;
		int8 ComputerWinCnt = GameInstance->ComputerWinCnt;

		// 플레이어 세트 승리 수 설정
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

		// 컴퓨터 세트 승리 수 설정
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
			// 시간은 Countdown 액터에서 가져옴
			int32 Countdown = GameInstance->CountdownActor->CountdownTime;
			if (GameCountdownText)
				GameCountdownText->SetText(FText::FromString(FString::FromInt(Countdown)));
			if (Countdown == 0)
			{
				// 시간이 0이 되면 남은 체력에 따라 누가 이겼는지 결정하고 게임 종료 함수 실행
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
			// 시간은 Countdown 액터에서 가져옴
			int8 Countdown = GameInstance->CountdownActor->CountdownTime;
			if (GameCountdownText)
				GameCountdownText->SetText(FText::FromString(FString::FromInt(Countdown)));
			if (Countdown == 0)
			{
				// 시간이 0이 되면 남은 체력에 따라 누가 이겼는지 결정하고 게임 종료 함수 실행
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
	// 게임이 시작될 때 일어나야 할 일들

	// 게임 시작 전 3초 시간을 재주는 텍스트는 사라지도록 함
	if (CountdownBeforeGameText)
		CountdownBeforeGameText->SetText(FText::FromString(TEXT("")));

	// 사용자의 컨트롤러를 플레이어 캐릭터에게 넘겨줌
	GetWorld()->GetFirstPlayerController()->Possess(PlayerCharacter);

	// UpdateCountdownBerforeGameText 함수를 더 이상 호출하지 않음
	bGameStart = true;

	// 60초 카운트다운 시작
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
				// 게임 시작 전까지 몇 초 남았는지 가져옴
				int8 Countdown = GameInstance->CountdownActor->CountdownBeforeStartAfterEnd;
				if (CountdownBeforeGameText)
				{
					// 시간이 남았으면 시간으로, 시간이 0이 된 순간 0 대신 Go!로 설정
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
					// 게임 시작 전까지 몇 초 남았는지 가져옴
					int32 Countdown = GameInstance->CountdownActor->CountdownBeforeStartAfterEnd;
					if (CountdownBeforeGameText)
					{
						// 시간이 남았으면 시간으로, 시간이 0이 된 순간 0 대신 Go!로 설정
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
		// 두 캐릭터의 현재 체력을 읽어와서 누가 이겼는지 판단하고
		// 그에 따라 승리 함수 실행
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