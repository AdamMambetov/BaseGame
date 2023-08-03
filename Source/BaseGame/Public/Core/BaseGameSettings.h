// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DataTable.h"
#include "Misc/Paths.h"
#include "GameplayTagsManager.h"
#include "BaseGameSettings.generated.h"

UCLASS(config = Plugins, defaultconfig, meta = (DisplayName = "Base Game"))
class BASEGAME_API UBaseGameSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UDataTable* GetAttacksDataTable();

    UDataTable* GetReciepesDataTable();

    UDataTable* GetMaterialsDataTable();

    UDataTable* GetPiecesDataTable();

    UDataTable* GetRawsDataTable();

    UDataTable* GetToolsDataTable();

    UDataTable* GetUtilsDataTable();

    UDataTable* GetWeaponsDataTable();

protected:
    UPROPERTY(EditAnywhere, config, Category = "Attack", meta = (MetaClass = "DataTable", DisplayName = "Attacks Data Table"))
    FSoftObjectPath AttacksDataTableRef;

    UPROPERTY()
    UDataTable* AttacksDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Crafting", meta = (MetaClass = "DataTable", DisplayName = "Reciepes Data Table"))
    FSoftObjectPath ReciepesDataTableRef;

    UPROPERTY()
    UDataTable* ReciepesDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Materials Data Table"))
    FSoftObjectPath MaterialsDataTableRef;

    UPROPERTY()
    UDataTable* MaterialsDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Pieces Data Table"))
    FSoftObjectPath PiecesDataTableRef;

    UPROPERTY()
    UDataTable* PiecesDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Raws Data Table"))
    FSoftObjectPath RawsDataTableRef;

    UPROPERTY()
    UDataTable* RawsDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Tools Data Table"))
    FSoftObjectPath ToolsDataTableRef;

    UPROPERTY()
    UDataTable* ToolsDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Utils Data Table"))
    FSoftObjectPath UtilsDataTableRef;

    UPROPERTY()
    UDataTable* UtilsDataTable;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (MetaClass = "DataTable", DisplayName = "Weapons Data Table"))
    FSoftObjectPath WeaponsDataTableRef;

    UPROPERTY()
    UDataTable* WeaponsDataTable;

public:
    UPROPERTY(EditAnywhere, config, Category = "Stat", meta = (DisplayName = "Stats Tag Root"))
    FGameplayTag StatsRoot;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (DisplayName = "Items Tag Root"))
    FGameplayTag ItemsRoot;

    UPROPERTY(EditAnywhere, config, Category = "Inventory", meta = (DisplayName = "Slot Containers Tag Root"))
    FGameplayTag SlotContainersRoot;

    UPROPERTY(EditAnywhere, config, Category = "Attack", meta = (DisplayName = "Attacks Tag Root"))
    FGameplayTag AttacksRoot;

    UPROPERTY(EditAnywhere, config, Category = "Crafting", meta = (DisplayName = "Reciepes Tag Root"))
    FGameplayTag ReciepesRoot;
};
