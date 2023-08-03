// Copyright UC Games, Inc. All Rights Reserved.

#include "Stats/StatsComponent.h"
#include "Net/UnrealNetwork.h"
#include "Core/Defaults.h"
#include "GameplayTagsManager.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

UStatsComponent::UStatsComponent()
{
    SetIsReplicated(true);
    PrimaryComponentTick.bCanEverTick = true;
}

void UStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    Server_InitStats();

    GetWorld()->GetTimerManager().SetTimer(RegenTimer, this, &UStatsComponent::RegenerateStats, RegenerationFrequency, true);
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UStatsComponent, Stats);
    DOREPLIFETIME(UStatsComponent, bDeath);
}

void UStatsComponent::Server_InitStats_Implementation()
{
    Stats.Empty();
    for (auto& Stat : InitialStats)
    {
        if (!UDefaults::IsValidStatId(Stat.Id)) continue;
        if (FMath::IsNearlyZero(Stat.MaxValue) || Stat.MaxValue < 0.f) continue;

        Stat.CurrentValue = FMath::Clamp(Stat.CurrentValue, Stat.CurrentValue, Stat.MaxValue);

        if (Stat.bCanRegenerate)
        {
            Stat.RegenerationStartDateTime = CalculateDateTime(Stat.RegenerationDelay);
        }

        Stats.Add(Stat);
    }
}

void UStatsComponent::Server_SetDead_Implementation()
{
    bDeath = true;
}

void UStatsComponent::RegenerateStats()
{
    for (const auto& Stat : Stats)
    {
        if (!CanRegenerateStat(Stat)) continue;

        FStatModifier StatModifier;
        StatModifier.Value = Stat.RegenerationRate * RegenerationFrequency;
        StatModifier.StatId = Stat.Id;
        StatModifier.ValueTag = UDefaults::MakeTag("StatModifier.Value.Current");

        Server_ModifyStat(StatModifier);
    }
}

bool UStatsComponent::GetStatInfo(const FGameplayTag& StatId, FStatInfo& Result) const
{
    if (!UDefaults::IsValidStatId(StatId)) return false;
    for (auto Stat : Stats)
        if (Stat.Id == StatId)
        {
            Result = Stat;
            return true;
        }
    return false;
}

bool UStatsComponent::CanRegenerateStat_Implementation(const FStatInfo& Stat) const
{
    FStatInfo L_Temp;
    if (!GetStatInfo(Stat.Id, L_Temp)) return false;

    return Stat.bCanRegenerate && !bDeath && FDateTime::Now() > Stat.RegenerationStartDateTime && Stat.CurrentValue < Stat.MaxValue;
}

FDateTime UStatsComponent::CalculateDateTime(const float Time)
{
    auto Now = FDateTime::Now();

    return FDateTime(Now.GetYear(), Now.GetMonth(), Now.GetDay(), Now.GetHour(), Now.GetMinute(), //
        Now.GetSecond() + FMath::TruncToInt(Time), Now.GetMillisecond() + (FMath::Fmod(Time, 1.f) * 1000.f));
}

bool UStatsComponent::Server_ModifyStat_Validate(const FStatModifier& StatModifier)
{
    FStatInfo L_TempStat;
    if (!GetStatInfo(StatModifier.StatId, L_TempStat)) return false;
    if (UDefaults::GetTagParent(StatModifier.ValueTag) != UDefaults::MakeTag("StatModifier.Value")) return false;

    return true;
}

void UStatsComponent::Server_ModifyStat_Implementation(const FStatModifier& StatModifier)
{
    for (auto& Stat : Stats)
    {
        if (Stat.Id != StatModifier.StatId) continue;

        if (StatModifier.ValueTag == UDefaults::MakeTag("StatModifier.Value.Current"))
        {
            Stat.CurrentValue = FMath::Clamp(Stat.CurrentValue + StatModifier.Value, 0.f, Stat.MaxValue);
            if (FMath::IsNearlyZero(Stat.CurrentValue))
            {
                OnStatReachedZero.Broadcast(Stat);
            }
        }

        if (StatModifier.ValueTag == UDefaults::MakeTag("StatModifier.Value.Max"))
        {
            Stat.MaxValue = FMath::Clamp(Stat.MaxValue + StatModifier.Value, 0.f, 99999.f);
            Stat.CurrentValue = FMath::Clamp(Stat.CurrentValue, 0.f, Stat.MaxValue);

            if (FMath::IsNearlyZero(Stat.CurrentValue))
            {
                OnStatReachedZero.Broadcast(Stat);
            }
        }

        if (StatModifier.ValueTag == UDefaults::MakeTag("StatModifier.Value.Regen"))
        {
            Stat.RegenerationRate = FMath::Clamp(Stat.RegenerationRate + StatModifier.Value, 0.f, 99999.f);
        }

        Server_CallOnStatChanged(Stat);
        return;
    }
}

void UStatsComponent::Server_CallOnStatChanged_Implementation(const FStatInfo& StatInfo)
{
    Multi_CallOnStatChanged(StatInfo);
}

bool UStatsComponent::Server_CallOnStatChanged_Validate(const FStatInfo& StatInfo)
{
    return Stats.ContainsByPredicate([&StatInfo](const FStatInfo& Stat) { return (StatInfo.Id == Stat.Id); });
}

void UStatsComponent::Multi_CallOnStatChanged_Implementation(const FStatInfo& StatInfo)
{
    OnStatChangedHandle.Broadcast(StatInfo);
}
