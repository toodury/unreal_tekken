// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountdownTime = 60;
	bStartGame = false;
	bGoNextGame = false;
	CountdownForThreeSeconds = 3.0f;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::CountdownTimer, 1.0f, true);
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::CountdownTimer()
{
	if (bStartGame)
	{
		CountdownTime--;
		if (CountdownTime <= 0)
		{
			GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		}
	}
}

void ACountdown::TimerBeforeStart()
{
	CountdownForThreeSeconds--;
	if (CountdownForThreeSeconds < 0)
	{
		StopCountdownBeforeStart();
	}
}

void ACountdown::StartCountdownBeforeStart()
{
	CountdownForThreeSeconds = 3.0f;
	GetWorldTimerManager().SetTimer(TimerHandleForThreeSeconds, this, &ACountdown::TimerBeforeStart, 1.0f, true);
}

void ACountdown::StopCountdownBeforeStart()
{
	GetWorldTimerManager().ClearTimer(TimerHandleForThreeSeconds);
	bStartGame = true;
}

void ACountdown::TimerAfterEnd()
{
	CountdownForThreeSeconds--;
	if (CountdownForThreeSeconds <= 0)
	{
		StopCountdownAfterEnd();
	}
}

void ACountdown::StartCountdownAfterEnd()
{
	CountdownForThreeSeconds = 3.0f;
	GetWorldTimerManager().SetTimer(TimerHandleForThreeSeconds, this, &ACountdown::TimerAfterEnd, 1.0f, true);
}

void ACountdown::StopCountdownAfterEnd()
{
	GetWorldTimerManager().ClearTimer(TimerHandleForThreeSeconds);
	bGoNextGame = true;
}