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
	AuraAbilitySystemComponent->AbilityEquipped.AddUObject(this, &USpellMenuWidgetController::OnAbilityEquipped);
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
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag& AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingEquipDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	if (AbilityTag.MatchesTagExact(SelectedAbility.Ability)
		|| !AbilityTag.IsValid()
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

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag& AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	WaitForEquipDelegate.Broadcast(AbilityType);
	bWaitingForEquipSelection = true;

	if (SelectedAbility.Status.MatchesTag(FAuraGameplayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot = AuraAbilitySystemComponent->GetInputTagFromAbilityTag(SelectedAbility.Ability);
	}
	else
	{
		SelectedSlot = FGameplayTag();
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag)
{
	if (!bWaitingForEquipSelection)return;

	const FGameplayTag& SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;

	if (SlotTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag.Passive"))))
	{
		if (!SelectedAbilityType.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Type_Passive))return;
	}
	else
	{
		if (!SelectedAbilityType.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Type_Offensive))return;
	}
	AuraAbilitySystemComponent->ServerEquipAbility(SelectedAbility.Ability, SlotTag);	
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
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
	
	StopWaitingEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType);
	GlobeDeselect();
	
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
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag& AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingEquipDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}

	SelectedAbility.Ability = FGameplayTag();
	SelectedAbility.Status = FGameplayTag();
	BroadcastButtonStates();
}
