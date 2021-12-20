// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_StartAttack.generated.h"

/**
 * 
 */
UCLASS()
class TEKKEN_API UAnimNotify_StartAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	// 캐릭터들의 공격 애니메이션에서 사용할 애님 노티파이
	// 공격 시작 의미
	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
