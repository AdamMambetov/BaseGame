// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stats/StatInfo.h"
#include "Stats/StatModifier.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, FStatInfo, StatInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatReachedZero, FStatInfo, StatInfo);

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class BASEGAME_API UStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Default Constructor
    UStatsComponent();

protected:
    // UActorComponent Component Begin

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // UActorComponent Component End

protected:
    // UStatsComponent Functions Begin

    UFUNCTION(Server, Reliable)
    void Server_InitStats();
    void Server_InitStats_Implementation();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent", meta = (DisplayName = "Set Dead", HideSelfPin))
    void Server_SetDead();
    void Server_SetDead_Implementation();

    void RegenerateStats();

    void ModifierTimer();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "BaseGame | StatsComponent")
    bool CanRegenerateStat(const FStatInfo& Stat) const;
    bool CanRegenerateStat_Implementation(const FStatInfo& Stat) const;

public:
    UFUNCTION(BlueprintPure, Category = "BaseGame | StatsComponent", meta = (AutoCreateRefTerm = "StatId"))
    bool GetStatInfo(const FGameplayTag& StatId, FStatInfo& Result) const;

    UFUNCTION(BlueprintPure, Category = "BaseGame | StatsComponent")
    FDateTime CalculateDateTime(const float Time);

    UFUNCTION(BlueprintCallable, Category = "BaseGame | StatsComponent")
    void AddModifier(FStatModifier Modifier);

    UFUNCTION(BlueprintCallable, Category = "BaseGame | StatsComponent")
    void RemoveModifier(FStatModifier Modifier);

    UFUNCTION(BlueprintGetter)
    TArray<FStatInfo> GetStats() const { return Stats; }

    UFUNCTION(BlueprintGetter)
    TArray<FStatModifier> GetModifiers() const { return Modifiers; }

    UFUNCTION(BlueprintGetter)
    bool IsDead() { return bDeath; }

    UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent", //
        meta = (DisplayName = "Modify Stat"))
    void Server_ModifyStat(const FStatModifier& StatModifier);
    bool Server_ModifyStat_Validate(const FStatModifier& StatModifier);
    void Server_ModifyStat_Implementation(const FStatModifier& StatModifier);

    UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent", //
        meta = (DisplayName = "CallOnStatChanged"))
    void Server_CallOnStatChanged(const FStatInfo& StatInfo);
    void Server_CallOnStatChanged_Implementation(const FStatInfo& StatInfo);
    bool Server_CallOnStatChanged_Validate(const FStatInfo& StatInfo);

    UFUNCTION(NetMulticast, Reliable)
    void Multi_CallOnStatChanged(const FStatInfo& StatInfo);
    void Multi_CallOnStatChanged_Implementation(const FStatInfo& StatInfo);

    // UStatsComponent Functions End

public:
    // UStatsComponent Dispatchers Begin

    UPROPERTY(BlueprintAssignable, Category = "BaseGame | StatsComponent")
    FOnStatChanged OnStatChangedHandle;

    UPROPERTY(BlueprintAssignable, Category = "BaseGame | StatsComponent")
    FOnStatReachedZero OnStatReachedZero;

    // UStatsComponent Dispatchers End

public:
    // UStatsComponent Variables Begin

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | StatsComponent", //
    meta = (ExposeOnSpawn = true, NoResetToDefault, TitleProperty = "ID"))
    TArray<FStatInfo> InitialStats;

protected:
    UPROPERTY(Replicated, BlueprintGetter = GetStats, Category = "BaseGame | StatsComponent")
    TArray<FStatInfo> Stats;

  

    UPROPERTY(EditAnywhere, BlueprintGetter = GetModifiers, Category = "BaseGame | StatsComponent", //
        meta = (NoResetToDefault, TitleProperty = "StatId"))
    TArray<FStatModifier> Modifiers;

    UPROPERTY(Replicated, BlueprintGetter = IsDead, Category = "BaseGame | StatsComponent")
    bool bDeath = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseGame | StatsComponent", meta = (ClampMin = 0.0001f, UIMin = 0.0001f))
    float RegenerationFrequency = 0.01f;

    UPROPERTY()
    FTimerHandle RegenTimer;

    UPROPERTY()
    FTimerHandle ModifierTimerHandle;

    // UStatsComponent Variables End
};
