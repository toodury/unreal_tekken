// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "tekkenGameModeBase.h"
#include "MyGameInstance.h"
#include "GameStartMenu.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UGameStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// 생성자
	virtual void NativeConstruct() override;

	// 이 위젯 내부에서 쓰일 로컬 변수들

	// 게임 모드
	UPROPERTY()
		AtekkenGameModeBase* GameMode;

	// 게임 인스턴스
	UPROPERTY()
		UMyGameInstance* GameInstance;

	// 현재 스폰되어 있는 캐릭터
	UPROPERTY()
		APawn* CurrentDisplayedCharacter;




	// 바인딩될 UI 위젯 항목들과 관련 함수, 변수들

	// 1. 닉네임 입력 Editable Text Box

	// 닉네임을 입력하는 텍스트 박스
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* PlayerNicknameInputTextBox;

	// 닉네임 입력 Editable Text Box 관련 초기화 함수
	UFUNCTION()
		void InitializePlayerNicknameInputTextBox();

	// 닉네임 입력이 유효한지 표시하는 bool 변수. 공백이 포함되어 있을 경우 true
	UPROPERTY()
		bool bNicknameInvalid;

	// 플레이어 닉네임에서 들어가면 안 될 문자 모음
	UPROPERTY()
		TArray<FString> InvalidNicknameArray;

	// 플레이어 닉네임 유효성 검사
	UFUNCTION(BlueprintCallable, Category = "PlayerNickname")
		bool IsNicknameValid(FString Nickname);

	// 유저가 입력한 닉네임을 임시 저장하기 위한 문자열 변수
	UPROPERTY()
		FString PlayerNicknameOnChange;

	// 닉네임을 입력하는 텍스트 박스에 문자가 입력될 때마다 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void PlayerNicknameInputTextBoxOnChange(const FText& Text);

	//// 닉네임을 입력하는 텍스트 박스에서 포커스가 아웃됐을 때 실행될 함수
	//UFUNCTION()
	//	void PlayerNicknameInputTextBoxOnCommitted(const FText& Text, ETextCommit::Type InCommitType);



	// 2. 닉네임 입력 오류 Text Block

	// 닉네임 입력 오류 텍스트
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NicknameWarningText;

	// 닉네임 입력 오류 텍스트 관련 초기화 함수
	UFUNCTION()
		void InitializeNicknameWarningText();

	// 닉네임 오류 문구를 띄울지 말지 결정하는 함수. 닉네임 입력 Editable Text Box의 OnChange 이벤트에 호출
	UFUNCTION()
		void DetermineNicknameWarningVisible();



	// 3. 플레이 Button

	// 플레이 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	// 플레이 버튼 텍스트
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PlayButtonText;

	// 플레이 버튼 관련 초기화 함수
	UFUNCTION()
		void InitializePlayButton();

	// 플레이 버튼을 눌렀을 때 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void PlayButtonClicked();

	// 플레이 버튼이 활성화될지 결성하는 함수. 닉네임 입력 Editable Text Box의 OnChange 이벤트와 캐릭터 선택 버튼의 OnClick 이벤트에서 호출
	UFUNCTION()
		void DeterminePlayButtonEnabled();



	// 4. Back Button

	// Back 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	// Back 버튼 텍스트
	UPROPERTY(meta = (BindWidget))
		UTextBlock* BackButtonText;

	// Back 버튼 관련 초기화 함수
	UFUNCTION()
		void InitializeBackButton();

	// Back 버튼을 눌렀을 때 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void BackButtonClicked();
	


	// 5. 캐릭터 선택 Button & Border

	// (0) 공통

	// 각 캐릭터별로 버튼이 선택되었는지 bool 변수를 저장한 map 변수
	UPROPERTY()
		TMap<ECharacters, bool> IsCharacterClickedMap;

	// 모든 캐릭터 버튼의 테두리를 저장한 Map
	UPROPERTY()
		TMap<ECharacters, UBorder*> CharacterBordersMap;

	// 캐릭터 선택 버튼들과 Border 관련 초기화. 캐릭터 추가시 추가 필요
	UFUNCTION()
		void InitializeCharacterSelectButtonsAndBorders();

	// 어떤 캐릭터 버튼이든 선택됐을 때 실행될 함수
	UFUNCTION()
		void AnyCharacterSelected(ECharacters SelectedCharacter);


	// (1) Wood Character

	// 나무 캐릭터 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* WoodCharacterSelectButton;

	// 나무 캐릭터 테두리
	UPROPERTY(meta = (BindWidget))
		UBorder* WoodCharacterBorder;

	// 나무 캐릭터 버튼을 눌렀을 때 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void WoodCharacterSelectButtonClicked();


	// (2) Ninja Character

	// 닌자 캐릭터 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* NinjaCharacterSelectButton;

	// 닌자 캐릭터 테두리
	UPROPERTY(meta = (BindWidget))
		UBorder* NinjaCharacterBorder;

	// 닌자 캐릭터 버튼을 눌렀을 때 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void NinjaCharacterSelectButtonClicked();

	
	// 새 캐릭터가 추가되면 Button, Border, Onclick 함수를 여기부터 추가하면 됨


	// (3) Random Character

	// 랜덤 캐릭터 버튼
	UPROPERTY(meta = (BindWidget))
		UButton* RandomCharacterSelectButton;

	// 랜덤 캐릭터 테두리
	UPROPERTY(meta = (BindWidget))
		UBorder* RandomCharacterBorder;

	// 랜덤 캐릭터 버튼을 눌렀을 때 실행될 함수
	UFUNCTION(BlueprintCallable, Category = "GameStartMenu")
		void RandomCharacterSelectButtonClicked();

};
