// Copyright KimDongChan


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	FString ExplainNumOfFireBolts = FString();
	if (Level == 1)
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Summon a shard of arcane energy, "
			"causing radial arcane damage of </>\n"));
	}
	else
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Summon %d shards of arcane energy, causing radial arcane damage of </>\n"), FMath::Min(Level, MaxNumShards));
	}
	return FString::Printf(TEXT(
		// Title
		"<Title>ARCANE SHARDS</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"%s"

		// Damage
		"<Damage>%d</><Default> at the shard origins.</>"),
						   Level,
						   ManaCost,
						   Cooldown,
						   *ExplainNumOfFireBolts,
						   ScaledDamage);
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	FString ExplainNumOfFireBolts = FString();
	if (Level == 1)
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Summon shards of arcane energy, "
			"causing radial damage of </>\n"));
	}
	else
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Summon %d shards of arcane energy, causing radial arcane damage of </>\n"), FMath::Min(Level, MaxNumShards));
	}
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"%s"

		// Damage
		"<Damage>%d</><Default> at the shard origins.</>"),
						   Level,
						   ManaCost,
						   Cooldown,
						   *ExplainNumOfFireBolts,
						   ScaledDamage);
}
