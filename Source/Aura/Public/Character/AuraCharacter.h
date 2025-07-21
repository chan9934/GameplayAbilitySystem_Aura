// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacter.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */


protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void InitAbilityActorInfo()override;

};
