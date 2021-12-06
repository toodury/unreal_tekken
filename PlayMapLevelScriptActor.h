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
    APlayMapLevelScriptActor();

    virtual void BeginPlay() override;

    // ���� ���
    UPROPERTY()
        AtekkenGameModeBase* GameMode;

    // ���� �ν��Ͻ�
    UPROPERTY()
        UMyGameInstance* GameInstance;

    // ���� ���� �� ����� �Լ�. ���� �������Ʈ���� Begin Play �̺�Ʈ�� ȣ���
    UFUNCTION(BlueprintCallable, Category = "PlayMap")
        void PlayMapBeginPlay();

};
