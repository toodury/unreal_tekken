// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	// 게임 시작 전 화면에서 사용할 플레이어 컨트롤러

protected:
	virtual void BeginPlay() override;
};
