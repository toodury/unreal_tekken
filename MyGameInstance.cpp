// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	PlayerCharacter = nullptr;
	ComputerCharacter = nullptr;
	PlayerWinCnt = 0;
	ComputerWinCnt = 0;
	Level = 1;
	CountdownActor = nullptr;
}