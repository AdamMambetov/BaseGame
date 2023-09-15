// Copyright UC Games, Inc. All Rights Reserved.

#include "Attack/DamageEndNotify.h"
#include "Attack/AttackComponent.h"

void UDamageEndNotify::Notify(                       //
    USkeletalMeshComponent* MeshComp,                //
    UAnimSequenceBase* Animation,                    //
    const FAnimNotifyEventReference& EventReference) //
{
    Super::Notify(MeshComp, Animation, EventReference);

    auto AttackComp = MeshComp->GetOwner()->GetComponentByClass<UAttackComponent>();
    if (!IsValid(AttackComp)) return;

    AttackComp->OnDamageEnd.Broadcast();
}
