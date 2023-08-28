#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attack/AttackState.h"
#include "Attack/AttackInfo.h"
#include "AttackComponent.generated.h"

class UDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackStart, FAttackInfo, AttackInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackEnd, FAttackInfo, AttackInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveCombo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetCombo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDamageStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDamageEnd);

enum class EAttackCollisionLocation : uint8
{
    Left,
    Right,
};

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class BASEGAME_API UAttackComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    // Default Constructor
    UAttackComponent();

protected:
    // UActorComponent Component Begin

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // UActorComponent Component End

public:
    // UAttackComponent Functions Begin

    UFUNCTION(BlueprintGetter)
    EAttackState GetAttackState() { return AttackState; }

    UFUNCTION(BlueprintGetter)
    FAttackInfo GetCurrentAttackInfo() { return CurrentAttackInfo; }

    UFUNCTION(BlueprintGetter)
    int32 GetComboCount() { return ComboCount; }

    UFUNCTION(BlueprintCallable, Category = "BaseGame | AttackComponent")
    virtual void Attack();

    UFUNCTION(BlueprintCallable, Category = "BaseGame | AttackComponent")
    virtual void AttackById(const FGameplayTag AttackId);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "BaseGame | AttackComponent")
    bool CanAttack();
    bool CanAttack_Implementation();

protected:
    UFUNCTION()
    virtual void OnAttackStartEvent(FAttackInfo AttackInfo);

    UFUNCTION()
    virtual void OnAttackEndEvent(FAttackInfo AttackInfo);

    UFUNCTION()
    virtual void OnSaveComboEvent();

    UFUNCTION()
    virtual void OnResetComboEvent();

    UFUNCTION(BlueprintCallable, Category = "BaseGame | AttackComponent")
    virtual FGameplayTag GetNextAttackId();

    // UAttackComponent Functions End

public:
    // UAttackComponent Dispatchers Begin

    UPROPERTY(BlueprintAssignable, Category = "BaseGame | AttackComponent")
    FOnAttackStart OnAttackStart;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "BaseGame | AttackComponent")
    FOnAttackEnd OnAttackEnd;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BaseGame | AttackComponent")
    FOnSaveCombo OnSaveCombo;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BaseGame | AttackComponent")
    FOnResetCombo OnResetCombo;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BaseGame | AttackComponent")
    FDamageStart OnDamageStart;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BaseGame | AttackComponent")
    FDamageEnd OnDamageEnd;

    // UAttackComponent Dispatchers End

protected:
    // UAttackComponent Variables Begin

    UPROPERTY(BlueprintGetter = GetAttackState, Category = "BaseGame | AttackComponent")
    EAttackState AttackState;

    UPROPERTY(BlueprintGetter = GetCurrentAttackInfo, Category = "BaseGame | AttackComponent")
    FAttackInfo CurrentAttackInfo;

    UPROPERTY(BlueprintGetter = GetComboCount, Category = "BaseGame | AttackComponent")
    int32 ComboCount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseGame | AttackComponent", meta = (AllowPrivateAccess = "true"))
    UDataTable* AttacksDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "BaseGame | AttackComponent")
    bool bIsRandomAttack = false;

    FGameplayTag NewAttackId;

    FGameplayTag CurrentCharacterId;

    EAttackCollisionLocation CollisionLocation;

    // UAttackComponent Variables End
};
