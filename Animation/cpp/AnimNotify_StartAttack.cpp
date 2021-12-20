// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_StartAttack.h"
#include "MyCharacter.h"

FString UAnimNotify_StartAttack::GetNotifyName_Implementation() const
{
	return L"StartAttack";
}

void UAnimNotify_StartAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	if (MyCharacter)
		MyCharacter->bAttacking = true;
}