﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterEnumClasses.h"
#include "MyCharacter.h"
#include "tekkenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API AtekkenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual	void BeginPlay() override;

public:

	// 캐릭터 스폰 관련

	// 게임의 모든 캐릭터를 맵으로 저장. 블루프린트에서 각 캐릭터 아이디에 맞게 캐릭터 직접 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
		TMap<ECharacters, TSubclassOf<APawn>> Characters;

	// Characters 맵에서 해당 캐릭터의 APawn 클래스를 반환하는 함수. 액터를 스폰할 때 사용
	UFUNCTION(BlueprintCallable, Category = "Characters")
		TSubclassOf<APawn> GetCharacterClass(ECharacters CharacterToSpawn);

	// 화면에 선택된 캐릭터를 정해진 위치에 스폰하는 함수. 블루프린트에서 정의
	UFUNCTION(BlueprintImplementableEvent, Category = "Characters")
		void SpawnCharacter(ECharacters CharacterToSpawn, FTransform CharacterSpawnTransform, APawn*& CurrentDisplayedCharacter);
	//UFUNCTION()
	//	APawn* SpawnCharacter(ECharacters CharacterToSpawn, FTransform CharacterSpawnTransform);



	// 위젯 관련

	// 화면에 표시된 위젯 전부 삭제 후 위젯 추가
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidget);

	// 화면에 표시된 위젯 전부 삭제
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void ClearWidget();

	// 위젯 추가
	UFUNCTION(BlueprintCallable, Category = "Widget")
		void AddWidget(TSubclassOf<UUserWidget> NewWidget);

	// 게임 시작시 표시할 메뉴 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<UUserWidget> StartingWidget;

	// 게임 플레이시 화면 상단에 표시될 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<UUserWidget> GamePlayWidget;

	// 현재 화면에 표시되고 있는 메뉴 위젯 TArray
	UPROPERTY()
		TArray<UUserWidget*> CurrentWidgets;



	// 레벨 관련

	// 레벨 이동
	UFUNCTION(BlueprintCallable, Category = "TransferLevel")
		void ChangeLevel(FString TransferLevelName);
};
