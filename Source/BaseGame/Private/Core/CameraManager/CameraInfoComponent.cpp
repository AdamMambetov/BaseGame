// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/CameraManager/CameraInfoComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"

UCameraInfoComponent::UCameraInfoComponent()
{
    // SetIsReplicated(true);
};

void UCameraInfoComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCameraInfoComponent, ViewMode);
}

void UCameraInfoComponent::BeginPlay()
{
    Super::BeginPlay();
    InitOwnerMesh();
}

void UCameraInfoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetOwner()) return;
    SetPivotTarget(GetOwner()->GetActorTransform());

    if (!OwnerMesh) return;
    SetFirstPersonPivotTarget(OwnerMesh->GetSocketLocation(FirstPersonCameraSocket));
}

void UCameraInfoComponent::SetPivotTarget(const FTransform NewPivotTarget)
{
    PivotTarget = NewPivotTarget;
}

void UCameraInfoComponent::SetFirstPersonPivotTarget(const FVector NewFirstPersonPivotTarget)
{
    FirstPersonPivotTarget = NewFirstPersonPivotTarget;
}

void UCameraInfoComponent::InitOwnerMesh()
{
    const FName OwnerMeshTag = "MainMesh";
    const TSubclassOf<USkeletalMeshComponent> ComponentClass = USkeletalMeshComponent::StaticClass();

    if (!GetOwner()) return;

    const auto OwnerMeshes = GetOwner()->GetComponentsByTag(ComponentClass, OwnerMeshTag);

    if (!OwnerMeshes.IsValidIndex(0)) return;

    OwnerMesh = Cast<USkeletalMeshComponent>(OwnerMeshes[0]);
}
