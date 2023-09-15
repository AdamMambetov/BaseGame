// Copyright UC Games, Inc. All Rights Reserved.

#include "Attack/ResetComboNotify.h"
#include "Attack/AttackComponent.h"

void UResetComboNotify::Notify(                      //
    USkeletalMeshComponent* MeshComp,                //
    UAnimSequenceBase* Animation,                    //
    const FAnimNotifyEventReference& EventReference) //
{
    Super::Notify(MeshComp, Animation, EventReference);

    auto AttackComp = MeshComp->GetOwner()->GetComponentByClass<UAttackComponent>();
    if (!IsValid(AttackComp)) return;

    AttackComp->OnResetCombo.Broadcast();
}
