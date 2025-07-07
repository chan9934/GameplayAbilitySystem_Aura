// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();


protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
};
