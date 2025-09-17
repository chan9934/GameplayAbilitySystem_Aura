// Copyright KimDongChan


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BraodcastAbilityInfo();
	GlobeDeselect();
	SpellPointsChanged.Broadcast(AuraPlayerState->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	AuraAbilitySystemComponent->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				BroadcastButtonStates();
			}
		});
	AuraPlayerState->OnSpellPointChangedDelegate.AddLambda(
		[this](int32 SpellPoints)
		{
			SpellPointsChanged.Broadcast(SpellPoints);
			BroadcastButtonStates();
		});
}

void USpellMenuWidgetController::BroadcastButtonStates()
{
	if (!SelectedAbility.Ability.IsValid() || !SelectedAbility.Status.IsValid())
	{
		SpellGlobeSelectedDelegate.Broadcast(false, false, FString(), FString());
		return;
	}
	int32 SpellPoints = AuraPlayerState->GetSpellPoints();
	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(SelectedAbility.Status, SpellPoints, bEnableSpendPoints, bEnableEquip);
	FString Description;
	FString NextLevelDescription;
	AuraAbilitySystemComponent->GetDescriptionByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	if (AbilityTag.MatchesTagExact(SelectedAbility.Ability)
		|| (!AbilityTag.IsValid() && !SelectedAbility.Ability.IsValid())
	)
	{
		GlobeDeselect();
		return;
	}

	FGameplayTag AbilityStatus;

	const bool bTagValid = AbilityTag.IsValid();
	FGameplayAbilitySpec* AbilitySpec = AuraAbilitySystemComponent->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;
	if (!bTagValid || !bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = AuraAbilitySystemComponent->GetStatusFromSpec(*AbilitySpec);
	}
	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	BroadcastButtonStates();
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	check(AuraAbilitySystemComponent);
	AuraAbilitySystemComponent->ServerSpendSpellPoint(SelectedAbility.Ability);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
                                                     bool& bShouldEnableSpellPointsButton,
                                                     bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;

	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped)
		|| AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		bShouldEnableSpellPointsButton = SpellPoints > 0 ? true : false;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		bShouldEnableSpellPointsButton = SpellPoints > 0 ? true : false;
	}
}

void USpellMenuWidgetController::GlobeDeselect()
{
	SelectedAbility.Ability = FGameplayTag();
	SelectedAbility.Status = FGameplayTag();
	BroadcastButtonStates();
}
