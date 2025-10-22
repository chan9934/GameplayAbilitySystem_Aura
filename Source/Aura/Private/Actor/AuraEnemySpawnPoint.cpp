// Copyright KimDongChan


#include "Actor/AuraEnemySpawnPoint.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

void AAuraEnemySpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAuraEnemy* Enemy = GetWorld()->SpawnActorDeferred<AAuraEnemy>(EnemyClass, GetActorTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Enemy->SetLevel(EnemyLevel);
	Enemy->FinishSpawning(GetActorTransform());
	Enemy->SpawnDefaultController();
}
