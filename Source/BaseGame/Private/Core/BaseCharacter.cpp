// Copyright UC Games, Inc. All Rights Reserved.

#include "Core/BaseCharacter.h"
#include "Stats/StatsComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

ABaseCharacter::ABaseCharacter() {}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABaseCharacter, CharacterState);
}

void ABaseCharacter::SetId(int32 NewId)
{
    if (NewId == ID || NewId < 0) return;

    UE_LOG(LogBaseCharacter, Display, TEXT("Set new ID in %s from %i to %i"), *UKismetSystemLibrary::GetDisplayName(this), ID, NewId);
    ID = NewId;
}

bool ABaseCharacter::ServerSetCharacterState_Validate(const FGameplayTag& NewCharacterState)
{
    const FGameplayTag CharacterStateTag = FGameplayTag::RequestGameplayTag(TEXT("CharacterState"));

    if (!CharacterStateTag.IsValid()) return false;

    return (!CharacterState.MatchesTagExact(NewCharacterState)) && NewCharacterState.MatchesTag(CharacterStateTag);
}

void ABaseCharacter::ServerSetCharacterState_Implementation(const FGameplayTag& NewCharacterState)
{
    CharacterState = NewCharacterState;
    MulticastCallOnCharacterStateChanged(NewCharacterState);
}

void ABaseCharacter::MulticastCallOnCharacterStateChanged_Implementation(const FGameplayTag& NewCharacterState)
{
    OnCharacterStateChanched.Broadcast(NewCharacterState);
}
