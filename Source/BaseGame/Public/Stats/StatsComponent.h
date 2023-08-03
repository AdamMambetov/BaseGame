// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stats/StatInfo.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, const FStatInfo&, StatInfo);

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "StatsComponent"))
class BASEGAME_API UStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UStatsComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    UFUNCTION(Server, Reliable, Category = "BaseGame | StatsComponent |")
    void Server_InitStats();
    void Server_InitStats_Implementation();

    UFUNCTION(Server, WithValidation, Reliable, Category = "BaseGame | StatsComponent |")
    void Server_RegenStart();
    void Server_RegenStart_Implementation();
    bool Server_RegenStart_Validate();

    UFUNCTION(Server, WithValidation, Reliable, Category = "BaseGame | StatsComponent |")
    void Server_RegenStop();
    void Server_RegenStop_Implementation();
    bool Server_RegenStop_Validate();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent |", meta = (DisplayName = "Set Dead", HideSelfPin))
    void Server_SetDead();
    void Server_SetDead_Implementation();

    void RegenerateStats();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "BaseGame | StatsComponent |")
    bool CanRegenerateStat(const FStatInfo& Stat) const;
    bool CanRegenerateStat_Implementation(const FStatInfo& Stat) const;

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BaseGame | StatsComponent |", meta = (AutoCreateRefTerm = "StatId", StatId = "Stat"))
    FStatInfo GetStatInfo(UPARAM(meta = (Categories = "Stat")) const FGameplayTag& StatId);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent |", meta = (DisplayName = "ModifyStat_SERVER"))
    void Server_ModifyStat(const FGameplayTag& StatId, const float Value, const bool bResetDelay);
    void Server_ModifyStat_Implementation(const FGameplayTag& StatId, const float Value, const bool bResetDelay = false);

    UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = "BaseGame | StatsComponent |", meta = (DisplayName = "CallOnStatChanged"))
    void Server_CallOnStatChanged(const FStatInfo& StatInfo);
    void Server_CallOnStatChanged_Implementation(const FStatInfo& StatInfo);
    bool Server_CallOnStatChanged_Validate(const FStatInfo& StatInfo);

    UFUNCTION(NetMulticast, Reliable, Category = "BaseGame | StatsComponent |")
    void Multi_CallOnStatChanged(const FStatInfo& StatInfo);
    void Multi_CallOnStatChanged_Implementation(const FStatInfo& StatInfo);

protected:
    UPROPERTY(BlueprintAssignable, Category = "BaseGame | StatsComponent |")
    FOnStatChanged OnStatChangedHandle;

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "BaseGame | StatsComponent |")
    TArray<FStatInfo> Stats;

    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, Category = "BaseGame | StatsComponent |", meta = (ExposeOnSpawn = true, NoResetToDefault, TitleProperty = "ID"))
    TArray<FStatInfo> InitialStats;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "BaseGame | StatsComponent |")
    bool bDeath;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseGame | StatsComponent |", meta = (ClampMin = 0.0001f))
    float RegenerationTimeInterval;

    UPROPERTY()
    FTimerHandle RegenTimer;

    UPROPERTY(Replicated)
    bool bRegenStarted;

    UPROPERTY()
    TMap<FGameplayTag, FDateTime> RegenDelayMap;
};
