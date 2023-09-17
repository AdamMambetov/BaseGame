// Copyright UC Games, Inc. All Rights Reserved.

#include "Attack/AttackEndNotify.h"
#include "Attack/AttackComponent.h"

void UAttackEndNotify::Notify(                       //
    USkeletalMeshComponent* MeshComp,                //
    UAnimSequenceBase* Animation,                    //
    const FAnimNotifyEventReference& EventReference) //
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (!IsValid(MeshComp)) return;
    if (!IsValid(MeshComp->GetOwner())) return;
    auto AttackComp = MeshComp->GetOwner()->GetComponentByClass<UAttackComponent>();
    if (!IsValid(AttackComp)) return;

    AttackComp->OnAttackEnd.Broadcast(AttackComp->GetCurrentAttackInfo());
}
