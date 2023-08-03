// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Core/ECharacterState.h"
#include "BaseCharacter.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanched, ECharacterState, CharacterState);

class UStatsComponent;

UCLASS()
class BASEGAME_API ABaseCharacter : public ACharacter, public IAISightTargetInterface, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    // Default Constructor
    ABaseCharacter();

    // Actor Begin

    virtual void Tick(float DeltaSeconds) override;

    // Actor End

public:
    // BaseCharacter Begin Functions

    UFUNCTION(BlueprintGetter, Category = "BaseGame | BaseCharacter | AI |")
    const int32 GetId() { return ID; }

    UFUNCTION(BlueprintSetter, Category = "BaseGame | BaseCharacter | AI |")
    const void SetId(int32 NewId);

    UFUNCTION(BlueprintGetter, Category = "BaseGame | BaseCharacter |")
    const ECharacterState GetCharacterState() { return CharacterState; }

    UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BaseGame | BaseCharacter |")
    void ServerSetCharacterState(ECharacterState NewCharacterState);
    bool ServerSetCharacterState_Validate(ECharacterState NewCharacterState);
    void ServerSetCharacterState_Implementation(ECharacterState NewCharacterState);

private:
    UFUNCTION(NetMulticast, Reliable, Category = "BaseGame | BaseCharacter |")
    void MulticastCallOnCharacterStateChanged(ECharacterState NewCharacterState);
    void MulticastCallOnCharacterStateChanged_Implementation(ECharacterState NewCharacterState);

    // BaseCharacter End Functions

protected:
    // BaseCharacter Begin Dispatchers

    UPROPERTY(BlueprintAssignable, Category = "BaseGame | BaseCharacter |")
    FOnCharacterStateChanched OnCharacterStateChanched;

    // BaseCharacter End Dispatchers

private:
    // BaseCharacter Begin Variables

    UPROPERTY(EditAnywhere, BlueprintGetter = GetId, BlueprintSetter = SetId, Category = "BaseGame | BaseCharacter | AI |")
    int32 ID = 0;

    UPROPERTY(Replicated, EditAnywhere, BlueprintGetter = GetCharacterState, Category = "BaseGame | BaseCharacter |")
    ECharacterState CharacterState;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseGame | BaseCharacter |")
    UStatsComponent* StatsComponent;

    // BaseCharacter End Variables
};