// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AuraGameplayTags.h"
#include "Aura/AuraLogChannels.h"
#include "Kismet/KismetSystemLibrary.h"

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

	//const int32 NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	const int32 NumProjectiles = FMath::Min(MaxNumProjectiles, MaxNumProjectiles);


	auto DrawFunction = [this, SocketLocation](FVector Direction)
	{
		FVector Start = SocketLocation +FVector(0,0,10);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start,
		                                     Start + Direction * 100.f, 5, FLinearColor::Red, 120,
		                                     2);
	};
	

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2, FVector::UpVector);

	
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation,
										 SocketLocation + LeftOfSpread * 100.f, 5, FLinearColor::White, 120,
										 2);
	
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation,
										 SocketLocation + LeftOfSpread.RotateAngleAxis(ProjectileSpread, FVector::UpVector) * 100.f, 5, FLinearColor::White, 120,
										 2);
	const float DeltaSpread = ProjectileSpread / (NumProjectiles-1);
	if (NumProjectiles > 1)
	{
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			DrawFunction(LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector));
		}
	}
	else
	{
			DrawFunction(Forward);
	}
}
