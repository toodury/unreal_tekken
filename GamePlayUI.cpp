// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayUI.h"

UGamePlayUI::UGamePlayUI(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	if (PlayerHp)
	{
		PlayerHp->BarFillType = EProgressBarFillType::LeftToRight;
	}

	if (ComputerHp)
	{
		ComputerHp->BarFillType = EProgressBarFillType::RightToLeft;
	}

	if (PlayerNicknameText)
	{
		PlayerNicknameText->SetText(FText::FromString(TEXT("Player")));
	}

	if (ComputerNicknameText)
	{
		ComputerNicknameText->SetText(FText::FromString(TEXT("Computer")));
	}


}