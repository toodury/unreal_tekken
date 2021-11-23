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
	UGameStartMenu(const FObjectInitializer& ObjectInitializer);

	// �� ���� ���ο��� ���� ���� ������

	// ���� ���
	UPROPERTY()
		AtekkenGameModeBase* GameMode;

	// ���� �ν��Ͻ�
	UPROPERTY()
		UMyGameInstance* GameInstance;

	// ���� �����Ǿ� �ִ� ĳ����
	UPROPERTY()
		APawn* CurrentDisplayedCharacter;




	// ���ε��� UI ���� �׸��� ���� �Լ�, ������

	// 1. �г��� �Է� Editable Text Box

	// �г����� �Է��ϴ� �ؽ�Ʈ �ڽ�
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* PlayerNicknameInputTextBox;

	// �г��� �Է� Editable Text Box ���� �ʱ�ȭ �Լ�
	UFUNCTION()
		void InitializePlayerNicknameInputTextBox();

	// �г��� �Է��� ��ȿ���� ǥ���ϴ� bool ����. ������ ���ԵǾ� ���� ��� true
	UPROPERTY()
		bool bNicknameInvalid;

	// �÷��̾� �г��ӿ��� ���� �� �� ���� ����
	UPROPERTY()
		TArray<FString> InvalidNicknameArray;

	// �÷��̾� �г��� ��ȿ�� �˻�
	UFUNCTION(BlueprintCallable, Category = "PlayerNickname")
		bool IsNicknameValid(FString Nickname);

	// ������ �Է��� �г����� �ӽ� �����ϱ� ���� ���ڿ� ����
	UPROPERTY()
		FString PlayerNicknameOnChange;

	// �г����� �Է��ϴ� �ؽ�Ʈ �ڽ��� ���ڰ� �Էµ� ������ ����� �Լ�
	UFUNCTION()
		void PlayerNicknameInputTextBoxOnChange(const FText& Text);

	//// �г����� �Է��ϴ� �ؽ�Ʈ �ڽ����� ��Ŀ���� �ƿ����� �� ����� �Լ�
	//UFUNCTION()
	//	void PlayerNicknameInputTextBoxOnCommitted(const FText& Text, ETextCommit::Type InCommitType);



	// 2. �г��� �Է� ���� Text Block

	// �г��� �Է� ���� �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NicknameWarningText;

	// �г��� �Է� ���� �ؽ�Ʈ ���� �ʱ�ȭ �Լ�
	UFUNCTION()
		void InitializeNicknameWarningText();

	// �г��� ���� ������ ����� ���� �����ϴ� �Լ�. �г��� �Է� Editable Text Box�� OnChange �̺�Ʈ�� ȣ��
	UFUNCTION()
		void DetermineNicknameWarningVisible();



	// 3. �÷��� Button

	// �÷��� ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	// �÷��� ��ư �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PlayButtonText;

	// �÷��� ��ư ���� �ʱ�ȭ �Լ�
	UFUNCTION()
		void InitializePlayButton();

	// �÷��� ��ư�� ������ �� ����� �Լ�
	UFUNCTION()
		void PlayButtonClicked();

	// �÷��� ��ư�� Ȱ��ȭ���� �Ἲ�ϴ� �Լ�. �г��� �Է� Editable Text Box�� OnChange �̺�Ʈ�� ĳ���� ���� ��ư�� OnClick �̺�Ʈ���� ȣ��
	UFUNCTION()
		void DeterminePlayButtonEnabled();



	// 4. Back Button

	// Back ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	// Back ��ư �ؽ�Ʈ
	UPROPERTY(meta = (BindWidget))
		UTextBlock* BackButtonText;

	// Back ��ư ���� �ʱ�ȭ �Լ�
	UFUNCTION()
		void InitializeBackButton();

	// Back ��ư�� ������ �� ����� �Լ�
	UFUNCTION()
		void BackButtonClicked();
	


	// 5. ĳ���� ���� Button & Border

	// (0) ����

	// �� ĳ���ͺ��� ��ư�� ���õǾ����� bool ������ ������ map ����
	UPROPERTY()
		TMap<ECharacters, bool> IsCharacterClickedMap;

	// ��� ĳ���� ��ư�� �׵θ��� ������ Map
	UPROPERTY()
		TMap<ECharacters, UBorder*> CharacterBordersMap;

	// ĳ���� ���� ��ư��� Border ���� �ʱ�ȭ. ĳ���� �߰��� �߰� �ʿ�
	UFUNCTION()
		void InitializeCharacterSelectButtonsAndBorders();

	// � ĳ���� ��ư�̵� ���õ��� �� ����� �Լ�
	UFUNCTION()
		void AnyCharacterSelected(ECharacters SelectedCharacter);


	// (1) Wood Character

	// ���� ĳ���� ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* WoodCharacterSelectButton;

	// ���� ĳ���� �׵θ�
	UPROPERTY(meta = (BindWidget))
		UBorder* WoodCharacterBorder;

	// ���� ĳ���� ��ư�� ������ �� ����� �Լ�
	UFUNCTION()
		void WoodCharacterSelectButtonClicked();


	// (2) Ninja Character

	// ���� ĳ���� ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* NinjaCharacterSelectButton;

	// ���� ĳ���� �׵θ�
	UPROPERTY(meta = (BindWidget))
		UBorder* NinjaCharacterBorder;

	// ���� ĳ���� ��ư�� ������ �� ����� �Լ�
	UFUNCTION()
		void NinjaCharacterSelectButtonClicked();

	
	// �� ĳ���Ͱ� �߰��Ǹ� Button, Border, Onclick �Լ��� ������� �߰��ϸ� ��


	// (3) Random Character

	// ���� ĳ���� ��ư
	UPROPERTY(meta = (BindWidget))
		UButton* RandomCharacterSelectButton;

	// ���� ĳ���� �׵θ�
	UPROPERTY(meta = (BindWidget))
		UBorder* RandomCharacterBorder;

	// ���� ĳ���� ��ư�� ������ �� ����� �Լ�
	UFUNCTION()
		void RandomCharacterSelectButtonClicked();

};
