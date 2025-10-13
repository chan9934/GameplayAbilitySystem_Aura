// Copyright KimDongChan


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}
	AuraPlayerState->OnAttributePointChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangeDelegate.Broadcast(Points);
		});
	AuraPlayerState->OnSpellPointChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			SpellPointsChangeDelegate.Broadcast(Points);
		});
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	AuraAbilitySystemComponent->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AuraAttributeSet);
	AttributeInfoDelegate.Broadcast(Info);

	AttributePointsChangeDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
	SpellPointsChangeDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}
