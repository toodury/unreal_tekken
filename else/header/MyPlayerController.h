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

	// ���� ���� �� ȭ�鿡�� ����� �÷��̾� ��Ʈ�ѷ�

protected:
	virtual void BeginPlay() override;
};
