// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/GameStartMenu.h"
#include "Internationalization/Text.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/header/RandomCharacter.h"
#include "Components/CanvasPanel.h"

#include <random>

void UGameStartMenu::NativeConstruct()
{
	// 로컬 변수 초기화

	GameMode = Cast<AtekkenGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentDisplayedCharacter = nullptr;

	// 닉네임 입력 Editable Text Box 관련 초기화
	InitializePlayerNicknameInputTextBox();

	// 닉네임 입력 오류 텍스트 관련 초기화
	InitializeNicknameWarningText();

	// 플레이 버튼 관련 초기화
	InitializePlayButton();

	// Back 버튼 관련 초기화
	InitializeBackButton();

	// 캐릭터 선택 버튼들과 Border 관련 초기화
	InitializeCharacterSelectButtonsAndBorders();
}

void UGameStartMenu::InitializePlayerNicknameInputTextBox()
{
	if (PlayerNicknameInputTextBox)
	{
		PlayerNicknameInputTextBox->SetHintText(FText::FromString(TEXT("닉네임은 최대 15자까지 가능합니다")));
		PlayerNicknameInputTextBox->SetKeyboardFocus();
		PlayerNicknameInputTextBox->OnTextChanged.AddDynamic(this, &UGameStartMenu::PlayerNicknameInputTextBoxOnChange);
	}

	// 초기 닉네임 입력이 되지 않은 상태이기 때문에 true로 초기화
	bNicknameInvalid = true;

	// 플레이어 닉네임에 공백 사용 불가
	InvalidNicknameArray = { TEXT(" ") };
}

bool UGameStartMenu::IsNicknameValid(FString Nickname)
{
	// 입력으로 들어온 텍스트가 유효하지 않은 문자를 포함하고 있는지 검사

	for (int32 i = 0; i < InvalidNicknameArray.Num(); i++)
	{
		if (Nickname.Contains(InvalidNicknameArray[i]))
		{
			return false;
		}
	}

	// 입력으로 들어온 텍스트가 적절한 길이(1자 이상 15자 이하)인지 검사
	int32 stringLen = Nickname.Len();
	if (stringLen < 1 || stringLen > 15)
		return false;

	return true;
}

void UGameStartMenu::PlayerNicknameInputTextBoxOnChange(const FText& Text)
{
	// 유저가 입력한 닉네임을 유효한지 검사한 후 플레이 버튼과 경고 문구 노출 여부 결정

	PlayerNicknameOnChange = Text.ToString();
	bNicknameInvalid = !IsNicknameValid(PlayerNicknameOnChange);
	DeterminePlayButtonEnabled();
	DetermineNicknameWarningVisible();
}

void UGameStartMenu::InitializeNicknameWarningText()
{
	if (NicknameWarningText)
	{
		NicknameWarningText->SetText(FText::FromString(TEXT("닉네임은 공백 입력이 불가능하고 15자 이하여야 합니다")));
		NicknameWarningText->SetColorAndOpacity(FSlateColor(FColor::Red));
		NicknameWarningText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UGameStartMenu::DetermineNicknameWarningVisible()
{
	if (bNicknameInvalid)
		NicknameWarningText->SetVisibility(ESlateVisibility::Visible);
	else
		NicknameWarningText->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameStartMenu::InitializePlayButton()
{
	if (PlayButton)
	{
		PlayButton->SetIsEnabled(false);
		PlayButton->OnClicked.AddDynamic(this, &UGameStartMenu::PlayButtonClicked);
	}

	if (PlayButtonText)
	{
		PlayButtonText->SetText(FText::FromString(TEXT("Play")));
	}
}

void UGameStartMenu::PlayButtonClicked()
{
	// 화면에 표시된 캐릭터 액터 파괴
	CurrentDisplayedCharacter->Destroy();

	// 게임 인스턴스에 플레이어가 입력한 닉네임 저장
	if (GameInstance)
		GameInstance->PlayerNickname = PlayerNicknameOnChange;

	// Play Map 열기
	if (GameMode)
		GameMode->ChangeLevel(TEXT("PlayMap"));
}

void UGameStartMenu::DeterminePlayButtonEnabled()
{
	// 닉네임이 유효하고 캐릭터가 선택되어 있어야 Play 버튼 활성화
	if (!bNicknameInvalid && CurrentDisplayedCharacter)
		PlayButton->SetIsEnabled(true);
}

void UGameStartMenu::InitializeBackButton()
{
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UGameStartMenu::BackButtonClicked);
	}

	if (BackButtonText)
	{
		BackButtonText->SetText(FText::FromString(TEXT("Back")));
	}
}

void UGameStartMenu::BackButtonClicked()
{
	// 현재 선택되어 있던 캐릭터가 있다면 화면에서 제거
	if (CurrentDisplayedCharacter)
		CurrentDisplayedCharacter->Destroy();

	// 메인 메뉴로 돌아감
	if (GameMode)
		GameMode->ChangeWidget(GameMode->StartingWidget);
}

void UGameStartMenu::InitializeCharacterSelectButtonsAndBorders()
{

	// 각 캐릭터별 OnClick 이벤트 함수 바인딩과 CharacterBordersMap에 항목 추가
	// 캐릭터 추가시 이걸 추가해주면 됨
	if (WoodCharacterSelectButton)
		WoodCharacterSelectButton->OnClicked.AddDynamic(this, &UGameStartMenu::WoodCharacterSelectButtonClicked);

	if (WoodCharacterBorder)
		CharacterBordersMap.Emplace(ECharacters::Wood, WoodCharacterBorder);

	if (NinjaCharacterSelectButton)
		NinjaCharacterSelectButton->OnClicked.AddDynamic(this, &UGameStartMenu::NinjaCharacterSelectButtonClicked);

	if (NinjaCharacterBorder)
		CharacterBordersMap.Emplace(ECharacters::Ninja, NinjaCharacterBorder);

	if (RandomCharacterSelectButton)
		RandomCharacterSelectButton->OnClicked.AddDynamic(this, &UGameStartMenu::RandomCharacterSelectButtonClicked);

	if (RandomCharacterBorder)
		CharacterBordersMap.Emplace(ECharacters::Random, RandomCharacterBorder);

	// IsCharacterClickedMap 초기화
	for (int32 i = 0; i <= static_cast<int32>(ECharacters::Random); i++)
		IsCharacterClickedMap.Emplace(static_cast<ECharacters>(i), false);

}

void UGameStartMenu::AnyCharacterSelected(ECharacters SelectedCharacter)
{
	// Game Instance에 선택된 캐릭터 저장

	if (GameInstance)
	{
		if (SelectedCharacter == ECharacters::Random)
		{
			// 랜덤 캐릭터가 선택되었을 경우 랜덤으로 캐릭터 설정
			std::random_device rd;
			std::mt19937 gen(rd());
			int CharacterNum = static_cast<int>(ECharacters::Random);	// 전체 캐릭터의 개수
			std::uniform_int_distribution<int> dis(0, CharacterNum - 1);

			int RandomNumber = dis(gen);	// 0 ~ 캐릭터 개수 - 1 사이에서 뽑은 랜덤 정수

			GameInstance->PlayerCharacterSelected = static_cast<ECharacters>(RandomNumber);
		}
		else
		{
			GameInstance->PlayerCharacterSelected = SelectedCharacter;
		}
	}

	// 모든 캐릭터 버튼의 클릭 상태를 false로 설정한 후 선택된 캐릭터만 true로 설정
	for (auto& Elem : IsCharacterClickedMap)
	{
		Elem.Value = false;
	}
	IsCharacterClickedMap[SelectedCharacter] = true;

	// 현재 화면에 소환되어 있는 캐릭터가 있다면 파괴
	if (CurrentDisplayedCharacter)
		CurrentDisplayedCharacter->Destroy();

	// 선택된 캐릭터 스폰
	if (GameMode)
	{
		FTransform CharacterSpawnTransform;
		if (SelectedCharacter == ECharacters::Random)
		{
			CharacterSpawnTransform.SetLocation(FVector(294.0f, 182.0f, 160.0f));
			CharacterSpawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, -180.0f)));
		}
		else
		{
			CharacterSpawnTransform.SetLocation(FVector(294.0f, 182.0f, 98.0f));
			CharacterSpawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 180.0f)));
		}
		GameMode->SpawnCharacter(SelectedCharacter, CharacterSpawnTransform, CurrentDisplayedCharacter);
	}

	// 플레이 버튼 활성화 여부 결정
	DeterminePlayButtonEnabled();

	// 선택된 캐릭터 버튼의 테두리를 빨간색으로, 나머지를 하얀색으로 설정
	for (auto& Elem : CharacterBordersMap)
	{
		Elem.Value->SetBrushColor(FLinearColor(FColor::White));
	}
	CharacterBordersMap[SelectedCharacter]->SetBrushColor(FLinearColor(FColor::Red));
}

void UGameStartMenu::WoodCharacterSelectButtonClicked()
{
	AnyCharacterSelected(ECharacters::Wood);
}

void UGameStartMenu::NinjaCharacterSelectButtonClicked()
{
	AnyCharacterSelected(ECharacters::Ninja);
}

void UGameStartMenu::RandomCharacterSelectButtonClicked()
{
	AnyCharacterSelected(ECharacters::Random);
}