// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanSaveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanSaveInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class BASEGAME_API ICanSaveInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanSaveInterface |")
    void Save(USaveGame* SaveGame);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CanSaveInterface |")
    void Load(USaveGame* SaveGame);
};
