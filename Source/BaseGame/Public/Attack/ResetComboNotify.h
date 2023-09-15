// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ResetComboNotify.generated.h"

UCLASS()
class BASEGAME_API UResetComboNotify : public UAnimNotify
{
    GENERATED_BODY()

    virtual void Notify(                                           //
        USkeletalMeshComponent* MeshComp,                          //
        UAnimSequenceBase* Animation,                              //
        const FAnimNotifyEventReference& EventReference) override; //
};