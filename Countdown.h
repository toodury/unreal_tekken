// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h"

UCLASS()
class TEKKEN_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 게임 진행 60초

	// 게임 진행 60초 카운트를 위한 변수
	//UPROPERTY(BlueprintReadOnly, Category = "Countdown")
	UPROPERTY()
		int8 CountdownTime;

	// 게임 진행 60초 카운트를 위한 타이머 핸들러
	UPROPERTY()
		FTimerHandle CountdownTimerHandle;

	// 게임 진행 60초 타이머 함수
	UFUNCTION()
		void CountdownTimer();

	// 게임 진행 60초 타이머 시작 함수
	UFUNCTION()
		void StartCountdownTimer();

	// 게임 진행 60초 타이머 종료 함수
	UFUNCTION()
		void StopCountdownTimer();



	// 게임 시작 전과 게임이 끝난 이후 3초

	// 게임 앞뒤 3초 대기를 위한 변수
//	UPROPERTY(BlueprintReadOnly, Category = "Countdown")
	UPROPERTY()
		int8 CountdownBeforeStartAfterEnd;
	// 타이머 핸들러
	UPROPERTY()
		FTimerHandle TimerHandleBeforeStartAfterEnd;

	// Before Start
	// 3초가 지나고 게임 시작을 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Countdown")
		bool bStartGame;
	// 게임 시작 이전 3초 카운트 타이머 함수
	UFUNCTION()
		void TimerBeforeStart();
	// 게임 시작 이전 3초 카운트 시작 함수
	UFUNCTION(BlueprintCallable, Category = "Countdown")
		void StartCountdownBeforeStart();
	// 게임 시작 이전 3초 카운트 종료 함수
	UFUNCTION(BlueprintCallable, Category = "Countdown")
		void StopCountdownBeforeStart();

	// After End
	// 게임 종료 이후 3초가 지난 후 다음 게임 시작을 의미하는 bool 변수
	UPROPERTY(BlueprintReadOnly, Category = "Countdown")
		bool bGoNextGame;
	// 게임 종료 이후 3초 카운트 타이머 함수
	UFUNCTION()
		void TimerAfterEnd();
	// 게임 종료 이후 3초 카운트 시작 함수
	UFUNCTION(BlueprintCallable, Category = "Countdown")
		void StartCountdownAfterEnd();
	// 게임 종료 이후 3초 카운트 종료 함수
	UFUNCTION(BlueprintCallable, Category = "Countdown")
		void StopCountdownAfterEnd();
};
