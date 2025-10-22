// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraEnemy.h"
#include "Engine/TargetPoint.h"
#include "AuraEnemySpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EnemyClass")
	TSubclassOf<AAuraEnemy> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EnemyClass")
	int32 EnemyLevel = 1;
};
