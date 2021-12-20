// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndAttack.h"
#include "MyCharacter.h"

FString UAnimNotify_EndAttack::GetNotifyName_Implementation() const
{
	return L"EndAttack";
}

void UAnimNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	if (MyCharacter)
		MyCharacter->bAttacking = false;
}