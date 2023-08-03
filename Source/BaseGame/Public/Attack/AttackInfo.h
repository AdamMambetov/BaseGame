//

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "AttackInfo.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FAttackInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInfo", meta = (Categories = "Character"))
    FGameplayTag Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInfo")
    UAnimMontage* Montage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackInfo", meta = (ClampMin = 0.f, UIMin = 0.f))
    float Damage;
};
