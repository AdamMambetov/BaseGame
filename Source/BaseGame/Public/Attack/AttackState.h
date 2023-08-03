//

#pragma once

#include "AttackState.generated.h"

UENUM(BlueprintType)
enum class EAttackState : uint8
{
    None UMETA(DisplayName = "None"),
    Attack UMETA(DisplayName = "Attack"),
    SaveCombo UMETA(DisplayName = "Save Combo"),
};
