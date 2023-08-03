// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "BaseCameraTypes.generated.h"

UENUM(BlueprintType)
enum class EViewMode : uint8
{
    FirstPerson UMETA(DisplayName = "First Person"),
    ThirdPerson UMETA(DisplayName = "Third Person"),
};
