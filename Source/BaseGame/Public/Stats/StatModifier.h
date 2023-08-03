// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/Defaults.h"
#include "StatModifier.generated.h"

USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct FStatModifier
{
    GENERATED_BODY()

    FStatModifier() {}

    FStatModifier(FString StatId, float Value, FString ValueTag)
    {
        this->StatId = UDefaults::MakeTag(StatId);
        this->Value = Value;
        this->ValueTag = UDefaults::MakeTag(ValueTag);
    }

    FStatModifier(FGameplayTag StatId, float Value, FGameplayTag ValueTag, FGameplayTag TypeTag, float Time, FDateTime EndDateTime)
    {
        this->StatId = StatId;
        this->Value = Value;
        this->ValueTag = ValueTag;
        this->TypeTag = TypeTag;
        this->Time = Time;
        this->EndDateTime = EndDateTime;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (Categories = "Stat")) FGameplayTag StatId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (ClampMin = 0.f))
    float Value = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (Categories = "StatModifier.Value"))
    FGameplayTag ValueTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (Categories = "StatModifier.Type"))
    FGameplayTag TypeTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (EditCondition = "bCanRegenerate", ClampMin = 0.f))
    float Time = 0.f;

    UPROPERTY(VisibleAnywhere, Category = "BaseGame | Stat |")
    FDateTime EndDateTime;
};
