// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "tekkenGameModeBase.h"
#include "MyGameInstance.h"
#include "PlayMapLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API APlayMapLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

    // 게임 모드
    UPROPERTY()
        AtekkenGameModeBase* GameMode;

    // 게임 인스턴스
    UPROPERTY()
        UMyGameInstance* GameInstance;

    // 레벨 시작 시 실행될 함수. 레벨 블루프린트에서 Begin Play 이벤트에 호출됨
    UFUNCTION(BlueprintCallable, Category = "PlayMap")
        void PlayMapBeginPlay();

};
