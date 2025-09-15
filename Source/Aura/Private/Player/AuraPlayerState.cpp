// Copyright KimDongChan


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
}

void AAuraPlayerState::SetLevel(int NewLevel)
{
	int32 AmountOfAttributePointsReward = 0;
	int32 AmountOfSpellPointsReward = 0; 
	for (int32 i = Level + 1; i <= NewLevel; ++i)
	{
		const FAuraLevelUpInfo AuraLevelUpInfo = GetLevelUpInfo()->GetLevelUpInfoForLevel(Level);
		AmountOfAttributePointsReward +=AuraLevelUpInfo.AttributePointAward;
		AmountOfSpellPointsReward += AuraLevelUpInfo.SpellPointAward;
	}
	
	Level = NewLevel;

	// ToDo Use AmountOfAttributePointsReward And AmountOfSpellPointsReward
	
	OnLevelChangedDelegate.Broadcast(NewLevel);
}

void AAuraPlayerState::AddToLevel(int AddLevel)
{
	Level += AddLevel;
	OnLevelChangedDelegate.Broadcast(AddLevel);
}

void AAuraPlayerState::SetXP(int NewXP)
{
	XP = NewXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToXP(int AddXP)
{
	XP += AddXP;
	OnXPChangedDelegate.Broadcast(XP);
}

int32 AAuraPlayerState::FindLevelForXP(int InXP)const
{
	return GetLevelUpInfo()->FindLevelForXP(InXP);
}

float AAuraPlayerState::GetXPPercent(bool& Success, int32 CurrentXP)const
{
	return GetLevelUpInfo()->GetXPPercent(Success, CurrentXP);
}

ULevelUpInfo* AAuraPlayerState::GetLevelUpInfo() const
{
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));
	return LevelUpInfo;
}

void AAuraPlayerState::OnRep_Level(int32 OldLEvel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
