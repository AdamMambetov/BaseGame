// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StatInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct FStatInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Stat", DisplayName = "Id"))
    FGameplayTag ID = FGameplayTag::RequestGameplayTag(FName("Stat"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.f))
    float CurrentValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.f))
    float MaxValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanRegenerate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCanRegenerate", ClampMin = 0.f))
    float RegenerationRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bCanRegenerate", Units = "Seconds", ClampMin = 0.f))
    float RegenerationDelay;
};
