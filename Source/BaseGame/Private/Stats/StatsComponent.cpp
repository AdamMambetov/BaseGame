// Copyright UC Games, Inc. All Rights Reserved.

#include "Stats/StatsComponent.h"
#include "Net/UnrealNetwork.h"
#include "Core/Defaults.h"
#include "GameplayTagsManager.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
    SetIsReplicatedByDefault(true);
    PrimaryComponentTick.bCanEverTick = true;

    bDeath = false;
    bRegenStarted = false;
    RegenerationTimeInterval = 0.0001f;
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    Server_InitStats();

    Server_RegenStart();
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UStatsComponent, Stats);
    DOREPLIFETIME(UStatsComponent, bDeath);
    DOREPLIFETIME(UStatsComponent, bRegenStarted);
}

void UStatsComponent::Server_InitStats_Implementation()
{
    Stats.Empty();
    for (auto Stat : InitialStats)
    {
        if (!UDefaults::IsValidStatId(Stat.ID)) continue;
        Stat.CurrentValue = Stat.MaxValue;
        Stats.Add(Stat);
    }
}

void UStatsComponent::Server_RegenStart_Implementation()
{
    GetWorld()->GetTimerManager().SetTimer(RegenTimer, this, &UStatsComponent::RegenerateStats, RegenerationTimeInterval, true);
    bRegenStarted = true;
}

bool UStatsComponent::Server_RegenStart_Validate()
{
    return (!bRegenStarted && !bDeath && GetWorld());
}

void UStatsComponent::Server_RegenStop_Implementation()
{
    GetWorld()->GetTimerManager().ClearTimer(RegenTimer);
    bRegenStarted = false;
    return;
}

bool UStatsComponent::Server_RegenStop_Validate()
{
    return bRegenStarted;
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
        if (RegenDelayMap.Contains(Stat.ID))
        {
            FDateTime* Before = RegenDelayMap.Find(Stat.ID);
            if (Before)
            {
                const FTimespan LDelay = FDateTime::Now() - *Before;
                if (LDelay.GetSeconds() > Stat.RegenerationDelay)
                    RegenDelayMap.Remove(Stat.ID);
                else if (Stat.RegenerationRate > 0.f)
                    continue;
            }
        }
        const float LValue = -1 * Stat.RegenerationRate * RegenerationTimeInterval;
        Server_ModifyStat(Stat.ID, LValue, false);
    }
}

bool UStatsComponent::CanRegenerateStat_Implementation(const FStatInfo& Stat) const
{
    return Stat.bCanRegenerate && !bDeath;
}

FStatInfo UStatsComponent::GetStatInfo(const FGameplayTag& StatId)
{
    if (!UDefaults::IsValidStatId(StatId)) return FStatInfo();
    for (auto Stat : Stats)
        if (Stat.ID == StatId) return Stat;
    return FStatInfo();
}

void UStatsComponent::Server_ModifyStat_Implementation(const FGameplayTag& StatId, const float Value, const bool bResetDelay)
{
    if (!UDefaults::IsValidStatId(StatId)) return;
    bool bLCanStartRegen = false;
    bool bLCanStopRegen = true;
    for (auto& Stat : Stats)
        if (Stat.ID == StatId)
        {
            const float Result = FMath::Clamp(Stat.CurrentValue - Value, 0.f, Stat.MaxValue);
            if (FMath::IsNearlyZero(Result))
            {
                if (FMath::IsNearlyZero(Stat.CurrentValue)) continue;
                Stat.CurrentValue = 0.f;
                Server_CallOnStatChanged(Stat);

                bLCanStopRegen = false;
                if (bResetDelay && Stat.bCanRegenerate && !FMath::IsNearlyZero(Stat.RegenerationRate))
                {
                    bLCanStartRegen = true;
                    if (bResetDelay)
                    {
                        RegenDelayMap.Remove(Stat.ID);
                        RegenDelayMap.Add(Stat.ID, FDateTime::Now());
                    }
                }
                continue;
            }

            if (FMath::IsNearlyEqual(Result, Stat.MaxValue))
            {
                if (FMath::IsNearlyEqual(Stat.CurrentValue, Stat.MaxValue)) continue;
                Stat.CurrentValue = Stat.MaxValue;
                Server_CallOnStatChanged(Stat);
                continue;
            }

            Stat.CurrentValue = Result;
            Server_CallOnStatChanged(Stat);
            bLCanStopRegen = false;
            if (bResetDelay && Stat.bCanRegenerate && !FMath::IsNearlyZero(Stat.RegenerationRate))
            {
                bLCanStartRegen = true;
                if (bResetDelay)
                {
                    RegenDelayMap.Remove(Stat.ID);
                    RegenDelayMap.Add(Stat.ID, FDateTime::Now());
                }
            }
            continue;
        }
    if (bLCanStartRegen) Server_RegenStart();
    if (bLCanStopRegen) Server_RegenStop();
    return;
}

void UStatsComponent::Server_CallOnStatChanged_Implementation(const FStatInfo& StatInfo)
{
    Multi_CallOnStatChanged(StatInfo);
}

bool UStatsComponent::Server_CallOnStatChanged_Validate(const FStatInfo& StatInfo)
{
    return Stats.ContainsByPredicate([&StatInfo](const FStatInfo& Stat) { return (StatInfo.ID == Stat.ID); });
}

void UStatsComponent::Multi_CallOnStatChanged_Implementation(const FStatInfo& StatInfo)
{
    OnStatChangedHandle.Broadcast(StatInfo);
}
