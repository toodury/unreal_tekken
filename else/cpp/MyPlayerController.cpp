// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	SetInputMode(FInputModeUIOnly());	// ���� ���� ���� UI�͸� ��ȣ�ۿ��ϵ��� �Է� ��� ����
	APlayerController::ConsoleCommand(TEXT("DisableAllScreenMessages"));	// ��ũ�� �޽��� ��Ȱ��ȭ
	bShowMouseCursor = true;	// ���콺 Ŀ�� ���̱�
}