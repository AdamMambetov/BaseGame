// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagsManager.h"
#include "Defaults.generated.h"

class UDataTable;

UCLASS()
class BASEGAME_API UDefaults : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults | Stat |")
    static bool IsValidStatId(const FGameplayTag& StatId);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults | Inventory |")
    static bool IsValidItemId(const FGameplayTag& ItemId);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults | Inventory |")
    static bool IsValidSlotContainerId(const FGameplayTag& SlotContainerId);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults | Attack |")

    static bool IsValidAttackId(const FGameplayTag& AttackId);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults |")
    static TArray<UDataTable*> GetDataTableList();

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults |")
    static TArray<FGameplayTag> GetChildrensByTag(const FGameplayTag Tag, const bool bAllChildrens = false);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults |")
    static TArray<FGameplayTag> GetTagParents(const FGameplayTag Tag);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults |")
    static FGameplayTag GetTagParent(const FGameplayTag Tag);

    UFUNCTION(BlueprintPure, Category = "BaseGame | Defaults |")
    static FGameplayTag MakeTagFromName(const FName TagName);
};
