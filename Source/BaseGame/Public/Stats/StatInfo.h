// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StatInfo.generated.h"

USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct FStatInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseGame | Stat |")
    FGameplayTag Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (ClampMin = 0.f))
    float CurrentValue = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (ClampMin = 0.f))
    float MaxValue = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |")
    bool bCanRegenerate = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |", meta = (EditCondition = "bCanRegenerate", ClampMin = 0.f))
    float RegenerationRate = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseGame | Stat |",
        meta = (EditCondition = "bCanRegenerate", Units = "Seconds", ClampMin = 0.f))
    float RegenerationDelay = 0.f;

    UPROPERTY(VisibleAnywhere, Category = "BaseGame | Stat |")
    FDateTime RegenerationStartDateTime;
};
