//

#include "Attack/AttackComponent.h"
#include "Core/Defaults.h"
#include "GameFramework/Actor.h"

UAttackComponent::UAttackComponent() {}

void UAttackComponent::BeginPlay()
{
    Super::BeginPlay();
    if (GetOwner())
    {
        CurrentCharacterId = UDefaults::MakeTagFromName(GetOwner()->Tags[0]);
    }

    OnAttackStart.AddDynamic(this, &UAttackComponent::OnAttackStartEvent);
    OnAttackEnd.AddDynamic(this, &UAttackComponent::OnAttackEndEvent);
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackComponent::Attack()
{
    switch (AttackState)
    {
    case EAttackState::None:
        AttackById(GetNextAttackId());
        break;
    case EAttackState::Attack:
        // AttackState = EAttackState::SaveCombo;
        break;
    case EAttackState::SaveCombo:
        // if ()
        break;
    }
}

void UAttackComponent::AttackById(const FGameplayTag AttackId)
{
    NewAttackId = AttackId;
    if (!CanAttack()) return;

    const auto L_NewAttackInfo = *AttacksDataTable->FindRow<FAttackInfo>(NewAttackId.GetTagName(), "");
    if (UDefaults::GetTagParent(L_NewAttackInfo.Id) != CurrentCharacterId) return;

    CurrentAttackInfo = L_NewAttackInfo;
    AttackState = EAttackState::Attack;
    // ComboCount = CurrentAttackInfo.ComboCount;
    OnAttackStart.Broadcast(CurrentAttackInfo);
}

bool UAttackComponent::CanAttack_Implementation()
{
    if (!AttacksDataTable) return false;
    return (AttackState != EAttackState::Attack && UDefaults::IsValidAttackId(NewAttackId) &&
            AttacksDataTable->GetRowNames().Contains(NewAttackId.GetTagName()));
}

void UAttackComponent::OnAttackStartEvent_Implementation(FAttackInfo AttackInfo) {}

void UAttackComponent::OnAttackEndEvent_Implementation(FAttackInfo AttackInfo)
{
    if (AttackInfo.Id != CurrentAttackInfo.Id) return;

    AttackState = EAttackState::None;
    ComboCount = 0;
    CurrentAttackInfo = FAttackInfo();
}

FGameplayTag UAttackComponent::GetNextAttackId()
{
    FGameplayTag ReturnValue = FGameplayTag::EmptyTag;

    auto Tags = UDefaults::GetChildrensByTag(CurrentCharacterId);
    if (Tags.Num() == 0 || !AttacksDataTable) return ReturnValue;

    while (!AttacksDataTable->GetRowNames().Contains(ReturnValue.GetTagName()))
    {
        ReturnValue = Tags[FMath::RandRange(0, Tags.Num() - 1)];
    }
    return ReturnValue;
}
