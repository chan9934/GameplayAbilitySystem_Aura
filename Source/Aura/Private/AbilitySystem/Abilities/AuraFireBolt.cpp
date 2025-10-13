// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing:</>\n"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),
		                       Level,
		                       ManaCost,
		                       Cooldown,
		                       ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolt of fire, "
			"exploding on impact and dealing:</>\n"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),
		                       Level,
		                       ManaCost,
		                       Cooldown,
		                       FMath::Min(Level, MaxNumProjectiles),
		                       ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing:</>\n"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),
		                       Level,
		                       ManaCost,
		                       Cooldown,
		                       ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolt of fire, "
			"exploding on impact and dealing:</>\n"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),
		                       Level,
		                       ManaCost,
		                       Cooldown,
		                       FMath::Min(Level, MaxNumProjectiles),
		                       ScaledDamage);
	}
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
                                     bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)Rotation.Pitch = PitchOverride;

	const int32 NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	//const int32 NumProjectiles = FMath::Min(MaxNumProjectiles, MaxNumProjectiles);
	
	const FVector Forward = Rotation.Vector();

	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	
		if (bLaunchHomingProjectiles && IsValid(HomingTarget))
		{
			if (HomingTarget->Implements<UCombatInterface>())
			{
				Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
			}
			else
			{
				Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
				Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
				Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;				
			}
			
			Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::RandRange(HomingAccelerationMin, HomingAccelerationMax);
			Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		}
		Projectile->FinishSpawning(SpawnTransform);
	}
}
