// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/CameraManager/BaseCameraTypes.h"
#include "CameraInfoComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BASEGAME_API UCameraInfoComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCameraInfoComponent();

    // ActorComponent Begin
protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // ActorComponent End

    // CameraInfoComponent Begin
public:
    UFUNCTION(BlueprintGetter, Category = "BaseGame | CameraInfoComponent |")
    EViewMode GetViewMode() const { return ViewMode; }

    UFUNCTION(BlueprintGetter, Category = "BaseGame | CameraInfoComponent |")
    FName GetFirstPersonCameraSocket() const { return FirstPersonCameraSocket; }

    UFUNCTION(BlueprintGetter, Category = "BaseGame | CameraInfoComponent |")
    FTransform GetPivotTarget() const { return PivotTarget; }

    UFUNCTION(BlueprintGetter, Category = "BaseGame | CameraInfoComponent |")
    FVector GetFirstPersonPivotTarget() const { return FirstPersonPivotTarget; }

    UFUNCTION(BlueprintGetter, Category = "BaseGame | CameraInfoComponent |")
    USkeletalMeshComponent* GetOwnerMesh() const { return OwnerMesh; }

protected:
    UFUNCTION(BlueprintSetter, Category = "BaseGame | CameraInfoComponent |")
    void SetPivotTarget(const FTransform NewPivotTarget);

    UFUNCTION(BlueprintSetter, Category = "BaseGame | CameraInfoComponent |")
    void SetFirstPersonPivotTarget(const FVector NewFirstPersonPivotTarget);

private:
    void InitOwnerMesh();

protected:
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "BaseGame | CameraInfoComponent |")
    EViewMode ViewMode;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetFirstPersonCameraSocket, Category = "BaseGame | CameraInfoComponent |")
    FName FirstPersonCameraSocket = "FirstPersonCameraSocket";

    UPROPERTY(BlueprintGetter = GetPivotTarget, BlueprintSetter = SetPivotTarget, Category = "BaseGame | CameraInfoComponent |")
    FTransform PivotTarget;

    UPROPERTY(BlueprintGetter = GetFirstPersonPivotTarget, BlueprintSetter = SetFirstPersonPivotTarget,
        Category = "BaseGame | CameraInfoComponent |")
    FVector FirstPersonPivotTarget;

    UPROPERTY(BlueprintGetter = GetOwnerMesh, Category = "BaseGame | CameraInfoComponent |")
    USkeletalMeshComponent* OwnerMesh;

    // CameraInfoComponent End
};
