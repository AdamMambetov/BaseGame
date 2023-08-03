// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/Defaults.h"
#include "GameplayTagsSettings.h"

bool UDefaults::IsValidStatId(const FGameplayTag& StatId)
{
    const FGameplayTag Root = MakeTag("Stat");

    if (!Root.IsValid()) return false;

    return GetChildrensByTag(Root, /**bAllChildrens*/ true).Contains(StatId);
}

bool UDefaults::IsValidItemId(const FGameplayTag& ItemId)
{
    const FGameplayTag Root = MakeTag("Item");

    if (!Root.IsValid()) return false;

    return GetChildrensByTag(Root, /**bAllChildrens*/ true).Contains(ItemId);
}

bool UDefaults::IsValidSlotContainerId(const FGameplayTag& SlotContainerId)
{
    const FGameplayTag Root = MakeTag("SlotContainer");

    if (!Root.IsValid()) return false;

    return GetChildrensByTag(Root, /**bAllChildrens*/ true).Contains(SlotContainerId);
}

bool UDefaults::IsValidAttackId(const FGameplayTag& AttackId)
{
    const FGameplayTag Root = MakeTag("Character");

    if (!Root.IsValid()) return false;

    return UGameplayTagsManager::Get().RequestGameplayTagChildren(Root).HasTagExact(AttackId);
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

    const FGameplayTag L_Root = GetTagParents(Tag).Last();
    TArray<FGameplayTag> AllTagsByRoot;
    UGameplayTagsManager::Get().RequestGameplayTagChildren(L_Root).GetGameplayTagArray(AllTagsByRoot);

    for (auto L_Tag : AllTagsByRoot)
    {
        if (!L_Tag.MatchesTag(Tag)) continue;

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
    if (ReturnArray.Num() == 0)
    {
        ReturnArray.Add(Tag);
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

FGameplayTag UDefaults::MakeTagFromName(const FName& TagName)
{
    return FGameplayTag::RequestGameplayTag(TagName);
}

FGameplayTag UDefaults::MakeTag(const FString& TagName)
{
    return FGameplayTag::RequestGameplayTag(FName(*TagName));
}
