// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DamageEndNotify.generated.h"

UCLASS()
class BASEGAME_API UDamageEndNotify : public UAnimNotify
{
    GENERATED_BODY()

    virtual void Notify(                                           //
        USkeletalMeshComponent* MeshComp,                          //
        UAnimSequenceBase* Animation,                              //
        const FAnimNotifyEventReference& EventReference) override; //
};
