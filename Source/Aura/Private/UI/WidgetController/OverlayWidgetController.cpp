// Copyright KimDongChan


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	check(AuraAbilitySystemComponent);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	AuraPlayerState->OnLevelChangedDelegate.AddLambda([this](int32 NewLevel, bool bLevelUp)
	{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel, bLevelUp);
	});

	AuraAbilitySystemComponent->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
	AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).
	                            AddLambda(
		                            [this](const FOnAttributeChangeData& Data)
		                            {
			                            OnHealthChanged.Broadcast(Data.NewValue);
		                            });
	AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).
	                            AddLambda(
		                            [this](const FOnAttributeChangeData& Data)
		                            {
			                            OnMaxHealthChanged.Broadcast(Data.NewValue);
		                            });
	AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).
	                            AddLambda(
		                            [this](const FOnAttributeChangeData& Data)
		                            {
			                            OnMaxManaChanged.Broadcast(Data.NewValue);
		                            });
	if (AuraAbilitySystemComponent->bStartupAbilitiesGiven)
	{
		BraodcastAbilityInfo();
	}
	else
	{
		AuraAbilitySystemComponent->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BraodcastAbilityInfo);
	}
	AuraAbilitySystemComponent->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			for (const FGameplayTag& Tag : TagContainer)
			{
				// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		});
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	bool bSuccess = false;
	const float XPBarPErcent = AuraPlayerState->GetXPPercent(bSuccess, NewXP);
	if (bSuccess)
	{
		OnXPPercentChangedDelegate.Broadcast(XPBarPErcent);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{

	const FAuraGameplayTags& GameplayTags = GameplayTags.Get();
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.InputTag = PreviousSlot;
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;	
	AbilityInfoDelegate.Broadcast(Info);
	
}
