// Copyright UC Games, Inc. All Rights Reserved.

#include "Attack/SaveComboNotify.h"
#include "Attack/AttackComponent.h"

void USaveComboNotify::Notify(                       //
    USkeletalMeshComponent* MeshComp,                //
    UAnimSequenceBase* Animation,                    //
    const FAnimNotifyEventReference& EventReference) //
{
    Super::Notify(MeshComp, Animation, EventReference);

    auto AttackComp = MeshComp->GetOwner()->GetComponentByClass<UAttackComponent>();
    if (!IsValid(AttackComp)) return;

    AttackComp->OnSaveCombo.Broadcast();
}
