// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/AuraLogChannels.h"


void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, ScaledDamage);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor,
	FVector InRadialDamageOrigin, bool bOverrideKnockbackDirection, FVector KnockbackDirecionOverride,
	bool bOverrideDeathImpulse, FVector DeathImpulseDirectionOverride, bool bOverridePitch, float PitchOverride) const
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffecClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;

	Params.DebuffChange = DebuffChange;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DebuffDuration = DebuffDuration;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;

	Params.KnockbackChance = KnockbackChance;
	Params.KnockbackMagnitude = KnockbackForceMagnitude;

	auto MakeImpulse = [&](FVector BaseDir, float Magnitude)
	{
		BaseDir.Normalize();
		FRotator Rotation = BaseDir.Rotation();
		if (bOverridePitch)
		{
			Rotation.Pitch = PitchOverride;
		}
		else
		{
			Rotation.Pitch = 45.f;
		}
		return Rotation.Vector() * Magnitude;
	};
	if (bOverrideKnockbackDirection)
	{
		Params.KnockbackForce = MakeImpulse(KnockbackDirecionOverride, KnockbackForceMagnitude);
	}
	else if (IsValid(TargetActor))
	{
		Params.KnockbackForce = MakeImpulse((TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()), KnockbackForceMagnitude);
	}

	if (bOverrideDeathImpulse)
	{
		Params.DeathImpulse = MakeImpulse(DeathImpulseDirectionOverride, DeathImpulseMagnitude);
	}
	else if (IsValid(TargetActor))
	{
		Params.DeathImpulse = MakeImpulse((TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()), DeathImpulseMagnitude);
	}

	if (bIsRadialDamage)
	{
		Params.bIsRadialDamage = bIsRadialDamage;
		Params.RadialDamageInnerRadius = RadialDamageInnerRadius;
		Params.RadialDamageOuterRadius = RadialDamageOuterRadius;
	}

	return Params;
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages)
{
	if (TaggedMontages.IsEmpty()) return FTaggedMontage();
	const int32 ArrayLength = TaggedMontages.Num();
	const int32 Selection = FMath::RandRange(0, ArrayLength - 1);
	return TaggedMontages[Selection];
}
