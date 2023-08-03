// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/CameraManager/BaseCameraManager.h"
#include "Net/UnrealNetwork.h"

ABaseCameraManager::ABaseCameraManager() : Super()
{
    SetReplicates(true);
};

// void ABaseCameraManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
//     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//     DOREPLIFETIME(ABaseCameraManager, PlayerCamera);
// }

// clang-format off

bool ABaseCameraManager::BlueprintUpdateCamera( 
    AActor* CameraTarget,                           
    FVector& NewCameraLocation,                     
    FRotator& NewCameraRotation,                    
    float& NewCameraFOV) // clang-format on
{
    // if (!PlayerCamera) return Super::BlueprintUpdateCamera(CameraTarget, NewCameraLocation, NewCameraRotation, NewCameraFOV);

    NewCameraFOV = DefaultFOV;
    return false;
}
