// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/AnimNotify_EndAttack.h"
#include "../../Character/header/MyCharacter.h"

FString UAnimNotify_EndAttack::GetNotifyName_Implementation() const
{
	// 노티파이 이름 설정
	return L"EndAttack";
}

void UAnimNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// 애니메이션이 적용될 캐릭터
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	// 해당 캐릭터를 공격 중이 아님으로 설정
	if (MyCharacter)
		MyCharacter->bAttacking = false;
}