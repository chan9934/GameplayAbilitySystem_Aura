// Copyright KimDongChan


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "EngineUtils.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* bilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
		                                 *FString::Printf(TEXT("GE Tag : %s"), *Tag.GetTagName().ToString()));
	}
}
