// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FTransform> UAuraSummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / (NumMinions - 1);

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FTransform> SpawnTransforms;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FTransform SpawnTransform;
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnTransform.SetLocation(ChosenSpawnLocation);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			SpawnTransform.SetLocation(Hit.ImpactPoint);
			SpawnTransform.SetRotation(FQuat::FindBetweenNormals(FVector::UpVector, Hit.ImpactNormal));
		}
			
		SpawnTransforms.Add(SpawnTransform);
	}
	return SpawnTransforms;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClass.Num() - 1);
	return MinionClass[Selection];
}
