// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/AnimNotify_StartAttack.h"
#include "../../Character/header/MyCharacter.h"

FString UAnimNotify_StartAttack::GetNotifyName_Implementation() const
{
	// ��Ƽ���� �̸� ����
	return L"StartAttack";
}

void UAnimNotify_StartAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// �ִϸ��̼��� ����Ǵ� ĳ����
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	// �ش� ĳ���͸� ���� ������ ����
	if (MyCharacter)
		MyCharacter->bAttacking = true;
}