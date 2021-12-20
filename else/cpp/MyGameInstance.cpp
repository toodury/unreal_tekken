// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	PlayerCharacter = nullptr;
	ComputerCharacter = nullptr;
	PlayerWinCnt = 0;
	ComputerWinCnt = 0;
	MaxLevel = static_cast<int8>(ECharacters::Random);
	CurrentLevel = 1;
	CountdownActor = nullptr;
}