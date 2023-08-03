// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "ECharacterState.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    HookMode UMETA(DisplayName = "HookMode"),
    BuildMode UMETA(DisplayName = "BuildMode"),
    BattleMode UMETA(DisplayName = "BattleMode"),
};