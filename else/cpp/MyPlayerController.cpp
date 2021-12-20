// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	SetInputMode(FInputModeUIOnly());	// 게임 시작 전엔 UI와만 상호작용하도록 입력 모드 설정
	APlayerController::ConsoleCommand(TEXT("DisableAllScreenMessages"));	// 스크린 메시지 비활성화
	bShowMouseCursor = true;	// 마우스 커서 보이기
}