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
    OnSaveCombo.AddDynamic(this, &UAttackComponent::OnSaveComboEvent);
    OnResetCombo.AddDynamic(this, &UAttackComponent::OnResetComboEvent);
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
        AttackState = bIsRandomAttack ? AttackState : EAttackState::SaveCombo;
        break;
    case EAttackState::SaveCombo:
        break;
    }
}

void UAttackComponent::AttackById(const FGameplayTag AttackId)
{
    NewAttackId = AttackId;
    if (!CanAttack()) return;
    if (UDefaults::GetTagParents(NewAttackId).Last(/*IndexFromTheEnd*/ 1) != CurrentCharacterId) return;

    const auto L_NewAttackInfo = *AttacksDataTable->FindRow<FAttackInfo>(NewAttackId.GetTagName(), "");
    CurrentAttackInfo = L_NewAttackInfo;
    AttackState = EAttackState::Attack;
    OnAttackStart.Broadcast(CurrentAttackInfo);
}

bool UAttackComponent::CanAttack_Implementation()
{
    if (!AttacksDataTable) return false;
    return (AttackState != EAttackState::Attack && UDefaults::IsValidAttackId(NewAttackId) &&
            AttacksDataTable->GetRowNames().Contains(NewAttackId.GetTagName()));
}

void UAttackComponent::OnAttackStartEvent(FAttackInfo AttackInfo) {}

void UAttackComponent::OnAttackEndEvent(FAttackInfo AttackInfo)
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
    if (Tags.Num() <= 1 || !IsValid(AttacksDataTable)) return ReturnValue;

    // Select next attack tag
    if (bIsRandomAttack)
        ReturnValue = Tags[FMath::RandRange(1, Tags.Num() - 1)];
    else
        ReturnValue = Tags.IsValidIndex(ComboCount + 1) ? Tags[ComboCount + 1] : FGameplayTag::EmptyTag;

    if (!ReturnValue.IsValid()) return ReturnValue;

    // Select attack tag by CollisionLocation (Left or Right)
    int32 ChildrenIndex = ((int32)CollisionLocation) + 1;
    ReturnValue = UDefaults::GetChildrensByTag(ReturnValue)[ChildrenIndex];

    return ReturnValue;
}

void UAttackComponent::OnSaveComboEvent()
{
    if (AttackState != EAttackState::SaveCombo) return;
    AttackState = EAttackState::None;
    ComboCount++;
    NewAttackId = FGameplayTag::EmptyTag;
    AttackById(GetNextAttackId());
}

void UAttackComponent::OnResetComboEvent()
{
    AttackState = EAttackState::None;
    CurrentAttackInfo = FAttackInfo();
    ComboCount = 0;
    NewAttackId = FGameplayTag::EmptyTag;
}
