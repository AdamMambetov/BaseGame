// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/BaseGameSettings.h"

UDataTable* UBaseGameSettings::GetAttacksDataTable()
{
    AttacksDataTable = Cast<UDataTable>(AttacksDataTableRef.ResolveObject());
    return AttacksDataTable;
}

UDataTable* UBaseGameSettings::GetReciepesDataTable()
{
    ReciepesDataTable = Cast<UDataTable>(ReciepesDataTableRef.ResolveObject());
    return ReciepesDataTable;
}

UDataTable* UBaseGameSettings::GetMaterialsDataTable()
{
    MaterialsDataTable = Cast<UDataTable>(MaterialsDataTableRef.ResolveObject());
    return MaterialsDataTable;
}

UDataTable* UBaseGameSettings::GetPiecesDataTable()
{
    PiecesDataTable = Cast<UDataTable>(PiecesDataTableRef.ResolveObject());
    return PiecesDataTable;
}

UDataTable* UBaseGameSettings::GetRawsDataTable()
{
    RawsDataTable = Cast<UDataTable>(RawsDataTableRef.ResolveObject());
    return RawsDataTable;
}

UDataTable* UBaseGameSettings::GetToolsDataTable()
{
    ToolsDataTable = Cast<UDataTable>(ToolsDataTableRef.ResolveObject());
    return ToolsDataTable;
}

UDataTable* UBaseGameSettings::GetUtilsDataTable()
{
    UtilsDataTable = Cast<UDataTable>(UtilsDataTableRef.ResolveObject());
    return UtilsDataTable;
}

UDataTable* UBaseGameSettings::GetWeaponsDataTable()
{
    WeaponsDataTable = Cast<UDataTable>(WeaponsDataTableRef.ResolveObject());
    return WeaponsDataTable;
}