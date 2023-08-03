// Copyright UC Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagsManager.h"
#include "BaseCharacter.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanched, const FGameplayTag&, CharacterState);

UCLASS()
class BASEGAME_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Default Constructor
    ABaseCharacter();

    // AActor Begin

    virtual void Tick(float DeltaSeconds) override;

    // AActor End

public:
    // ABaseCharacter Begin Functions

    UFUNCTION(BlueprintGetter)
    int32 GetId() const { return ID; }

    UFUNCTION(BlueprintSetter)
    void SetId(const int32 NewId);

    UFUNCTION(BlueprintGetter, Category = "BaseGame | BaseCharacter")
    FGameplayTag GetCharacterState() const { return CharacterState; }

    UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BaseGame | BaseCharacter",
        meta = (DisplayName = "Set Character State"))
    void ServerSetCharacterState(const FGameplayTag& NewCharacterState);
    bool ServerSetCharacterState_Validate(const FGameplayTag& NewCharacterState);
    void ServerSetCharacterState_Implementation(const FGameplayTag& NewCharacterState);

private:
    UFUNCTION(NetMulticast, Reliable, Category = "BaseGame | BaseCharacter")
    void MulticastCallOnCharacterStateChanged(const FGameplayTag& NewCharacterState);
    void MulticastCallOnCharacterStateChanged_Implementation(const FGameplayTag& NewCharacterState);

    // ABaseCharacter End Functions

protected:
    // ABaseCharacter Begin Dispatchers

    UPROPERTY(BlueprintAssignable, Category = "BaseGame | BaseCharacter")
    FOnCharacterStateChanched OnCharacterStateChanched;

    // ABaseCharacter End Dispatchers

private:
    // ABaseCharacter Begin Variables

    UPROPERTY(EditAnywhere, BlueprintGetter = GetId, BlueprintSetter = SetId, Category = "BaseGame | BaseCharacter")
    int32 ID = 0;

    UPROPERTY(Replicated, EditAnywhere, BlueprintGetter = GetCharacterState, Category = "BaseGame | BaseCharacter")
    FGameplayTag CharacterState;

    // ABaseCharacter End Variables
};