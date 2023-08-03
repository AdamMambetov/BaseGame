// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BaseCameraManager.generated.h"

UCLASS()
class BASEGAME_API ABaseCameraManager : public APlayerCameraManager
{
    GENERATED_BODY()

public:
    ABaseCameraManager();

    bool BlueprintUpdateCamera(AActor* CameraTarget, FVector& NewCameraLocation, FRotator& NewCameraRotation, float& NewCameraFOV);

protected:
    // UPROPERTY(Replicated, BlueprintReadOnly, Category="BaseGame | CameraManager")
    // class UBaseCameraManager* PlayerCamera;
};
