// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/AnimNotify_EndAttack.h"
#include "../../Character/header/MyCharacter.h"

FString UAnimNotify_EndAttack::GetNotifyName_Implementation() const
{
	// ��Ƽ���� �̸� ����
	return L"EndAttack";
}

void UAnimNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// �ִϸ��̼��� ����� ĳ����
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	// �ش� ĳ���͸� ���� ���� �ƴ����� ����
	if (MyCharacter)
		MyCharacter->bAttacking = false;
}