// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/Defaults.h"
#include "GameplayTagsManager.h"
#include "Core/BaseGameSettings.h"
#include "GameplayTagsSettings.h"

bool UDefaults::IsValidStatId(const FGameplayTag& StatId)
{
    auto Root = GetMutableDefault<UBaseGameSettings>()->StatsRoot;

    return UGameplayTagsManager::Get().RequestGameplayTagChildren(Root).HasTag(StatId);
}

bool UDefaults::IsValidItemId(const FGameplayTag& ItemId)
{
    auto Root = GetMutableDefault<UBaseGameSettings>()->ItemsRoot;

    return UGameplayTagsManager::Get().RequestGameplayTagChildren(Root).HasTag(ItemId);
}

bool UDefaults::IsValidSlotContainerId(const FGameplayTag& SlotContainerId)
{
    auto Root = GetMutableDefault<UBaseGameSettings>()->SlotContainersRoot;

    return UGameplayTagsManager::Get().RequestGameplayTagChildren(Root).HasTag(SlotContainerId);
}

bool UDefaults::IsValidAttackId(const FGameplayTag& AttackId)
{
    auto Root = GetMutableDefault<UBaseGameSettings>()->AttacksRoot;

    return UGameplayTagsManager::Get().RequestGameplayTagChildren(Root).HasTag(AttackId);
}

TArray<UDataTable*> UDefaults::GetDataTableList()
{
    TArray<UDataTable*> ReturnArray;
    auto TagSettings = GetMutableDefault<UGameplayTagsSettings>();

    for (auto Table : TagSettings->GameplayTagTableList)
    {
        ReturnArray.Add(Cast<UDataTable>(Table.ResolveObject()));
    }

    return ReturnArray;
}

TArray<FGameplayTag> UDefaults::GetChildrensByTag(const FGameplayTag Tag, const bool bAllChildrens)
{
    TArray<FGameplayTag> ReturnArray;
    if (!Tag.IsValid()) return ReturnArray;

    TArray<UDataTable*> DataTables = GetDataTableList();
    for (const auto& Table : DataTables)
    {
        TArray<FName> RowNames = Table->GetRowNames();
        for (const auto& RowName : RowNames)
        {
            FGameplayTag L_Tag = MakeTagFromName(RowName);

            if (Tag.MatchesTagExact(L_Tag))
            {
                ReturnArray.AddUnique(L_Tag);
                return ReturnArray;
            }

            if (!Tag.MatchesTag(L_Tag)) continue;

            if (!bAllChildrens)
            {
                auto Parents = GetTagParents(L_Tag);
                for (int32 i = 0; i < Parents.Num(); ++i)
                {
                    if (Parents[i] == Tag) break;

                    L_Tag = Parents[i];
                }
            }
            ReturnArray.AddUnique(L_Tag);
        }

        if (!ReturnArray.IsEmpty()) return ReturnArray;
    }

    return ReturnArray;
}
TArray<FGameplayTag> UDefaults::GetTagParents(const FGameplayTag Tag)
{
    TArray<FGameplayTag> ReturnArray;
    Tag.GetGameplayTagParents().GetGameplayTagArray(ReturnArray);
    return ReturnArray;
}

FGameplayTag UDefaults::GetTagParent(const FGameplayTag Tag)
{
    return Tag.RequestDirectParent();
}
FGameplayTag UDefaults::MakeTagFromName(const FName TagName)
{
    return FGameplayTag::RequestGameplayTag(TagName);
}
