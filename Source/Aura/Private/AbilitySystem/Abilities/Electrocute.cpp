// Copyright KimDongChan


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	FString ExplainNumOfFireBolts = FString();
	if (Level == 1)
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Emits a beam of Lightning, "
			"connecting with the target, repeatedly causing </>\n"));
	}
	else
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Emits a beam of Lightning, "
			"propagating to %d additional targets nearby, causing </>\n"), FMath::Min(Level, MaxNumShockTargets - 1));
	}
	return FString::Printf(TEXT(
		// Title
		"<Title>ELECTROCUTE</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		"%s"

		// Damage
		"<Damage>%d</><Default> fire damage with"
		" a chance to stun</>"),
						   Level,
						   ManaCost,
						   Cooldown,
						   *ExplainNumOfFireBolts,
						   ScaledDamage);
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	FString ExplainNumOfFireBolts = FString();
	if (Level == 1)
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Emits a beam of Lightning, "
			"connecting with the target, repeatedly causing </>\n"));
	}
	else
	{
		ExplainNumOfFireBolts = FString::Printf(TEXT("<Default>Emits a beam of Lightning, "
			"propagating to %d additional targets nearby, causing </>\n"), FMath::Min(Level, MaxNumShockTargets - 1));
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
		"<Damage>%d</><Default> lightning damage with"
		" a chance to stun</>"),
						   Level,
						   ManaCost,
						   Cooldown,
						   *ExplainNumOfFireBolts,
						   ScaledDamage);
}
