// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainMenuPawn.generated.h"

UCLASS()
class TEKKEN_API AMainMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	
	// 게임 시작 전 Menu Map에서 사용될 폰
	// 오직 UI하고만 상호작용해야 하므로 이동, 회전 불가
	AMainMenuPawn();
};
