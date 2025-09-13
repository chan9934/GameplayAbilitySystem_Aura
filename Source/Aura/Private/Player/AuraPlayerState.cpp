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
	Level = NewLevel;
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
	OnXPChangedDelegate.Broadcast(NewXP);
}

void AAuraPlayerState::AddToXP(int AddXP)
{
	XP += AddXP;
	OnXPChangedDelegate.Broadcast(AddXP);
}

float AAuraPlayerState::GetXPPercent(bool& Success, int32 CurrentXP)const
{
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));
	
	float XPPercent = 100.0f;
	
	const int32 CurrentLevel = LevelUpInfo->FindLevelForXP(CurrentXP);

	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num() - 1;
	if (CurrentLevel <= MaxLevel && CurrentLevel > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel -1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = CurrentXP - PreviousLevelUpRequirement;

		Success = true;
		return float(XPForThisLevel) / float(DeltaLevelRequirement);	
	}
	Success = false;
	return XPPercent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLEvel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
