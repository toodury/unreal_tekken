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

	FString GetNotifyName_Implementation() const;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
