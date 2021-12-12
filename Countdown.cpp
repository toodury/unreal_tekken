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
	CountdownBeforeStartAfterEnd = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();	
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
			StopCountdownTimer();
	}
}

void ACountdown::StartCountdownTimer()
{
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::CountdownTimer, 1.0f, true);
}

void ACountdown::StopCountdownTimer()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
}

void ACountdown::TimerBeforeStart()
{
	CountdownBeforeStartAfterEnd--;

	if (CountdownBeforeStartAfterEnd < 0)
	{
		StopCountdownBeforeStart();
	}
}

void ACountdown::StartCountdownBeforeStart()
{
	CountdownBeforeStartAfterEnd = 3;
	GetWorldTimerManager().SetTimer(TimerHandleBeforeStartAfterEnd, this, &ACountdown::TimerBeforeStart, 1.0f, true);
}

void ACountdown::StopCountdownBeforeStart()
{
	GetWorldTimerManager().ClearTimer(TimerHandleBeforeStartAfterEnd);
	bStartGame = true;
}

void ACountdown::TimerAfterEnd()
{
	CountdownBeforeStartAfterEnd--;
	if (CountdownBeforeStartAfterEnd <= 0)
	{
		StopCountdownAfterEnd();
	}
}

void ACountdown::StartCountdownAfterEnd()
{
	CountdownBeforeStartAfterEnd = 3;
	GetWorldTimerManager().SetTimer(TimerHandleBeforeStartAfterEnd, this, &ACountdown::TimerAfterEnd, 1.0f, true);
}

void ACountdown::StopCountdownAfterEnd()
{
	GetWorldTimerManager().ClearTimer(TimerHandleBeforeStartAfterEnd);
	bGoNextGame = true;
}