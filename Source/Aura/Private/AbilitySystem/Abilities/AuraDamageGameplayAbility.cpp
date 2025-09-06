// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAuraDamageGameplayAbility::SetDamageByDamageTypes(const FGameplayEffectSpecHandle& SpecHandle)
{
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float ScaledDamge = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamge);
	}
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages)
{
	if (TaggedMontages.IsEmpty()) return FTaggedMontage();
	const int32 ArrayLength = TaggedMontages.Num();
	const int32 Selection = FMath::RandRange(0, ArrayLength - 1);
	return TaggedMontages[Selection];
}
