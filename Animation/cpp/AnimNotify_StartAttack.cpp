// Fill out your copyright notice in the Description page of Project Settings.


#include "../header/AnimNotify_StartAttack.h"
#include "../../Character/header/MyCharacter.h"

FString UAnimNotify_StartAttack::GetNotifyName_Implementation() const
{
	// 노티파이 이름 설정
	return L"StartAttack";
}

void UAnimNotify_StartAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// 애니메이션이 적용되는 캐릭터
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());

	// 해당 캐릭터를 공격 중으로 설정
	if (MyCharacter)
		MyCharacter->bAttacking = true;
}