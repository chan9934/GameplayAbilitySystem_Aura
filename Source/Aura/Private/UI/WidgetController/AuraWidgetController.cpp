// Copyright KimDongChan


#include "UI/WidgetController/AuraWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

FWidgetControllerParams::FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AuraPlayerController = Cast<AAuraPlayerController>(PC);
	AuraPlayerState = Cast<AAuraPlayerState>(PS);
	AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(ASC);
	AuraAttributeSet = Cast<UAuraAttributeSet>(AS);
}


void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	AuraPlayerController = WidgetControllerParams.AuraPlayerController;
	AuraPlayerState = WidgetControllerParams.AuraPlayerState;
	AuraAbilitySystemComponent = WidgetControllerParams.AuraAbilitySystemComponent;
	AuraAttributeSet = WidgetControllerParams.AuraAttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}

void UAuraWidgetController::BraodcastAbilityInfo()
{
	if (!AuraAbilitySystemComponent->bStartupAbilitiesGiven)return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(
			UAuraAbilitySystemComponent::GetTagFromSpec(AbilitySpec, GameplayTags.AbilityTag_Root));
		Info.InputTag = UAuraAbilitySystemComponent::GetTagFromSpec(AbilitySpec, GameplayTags.InputTag_Root, true);
		Info.StatusTag = UAuraAbilitySystemComponent::GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
