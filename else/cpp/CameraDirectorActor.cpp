// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirectorActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirectorActor::ACameraDirectorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirectorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (OurPlayerController)
	{
		if (OurPlayerController->GetViewTarget() != Camera && Camera != nullptr)
		{
			OurPlayerController->SetViewTarget(Camera);
		}
	}
}

