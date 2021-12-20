// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/Countdown.h"

ACountdown::ACountdown()
{
	// 관련 변수 초기화

	CountdownTime = 60;
	bStartGame = false;
	bGoNextGame = false;
	CountdownBeforeStartAfterEnd = 3;
}

void ACountdown::CountdownTimer()
{
	// 게임이 시작했다면 60초 카운트다운 시작

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
	// 3초 이후 게임 시작

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
	// 3초가 지나면 다음 게임으로

	GetWorldTimerManager().ClearTimer(TimerHandleBeforeStartAfterEnd);
	bGoNextGame = true;
}