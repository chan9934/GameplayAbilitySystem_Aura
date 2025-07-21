// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface, public ICombatInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void BeginPlay() override;

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end Enemy Interface */
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

protected:
	virtual void InitAbilityActorInfo()override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
