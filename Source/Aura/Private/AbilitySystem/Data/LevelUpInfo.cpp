// Copyright KimDongChan


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)const
{
	//  level up information at one equals level one information
	// level up information at two equals level two information

	int32 Level = 1;
	if (LevelUpInformation.Num()-1 < Level)return Level;
	bool bSearching = true;
	
	while (bSearching)
	{
		if (LevelUpInformation[Level].LevelUpRequirement <=  XP)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}

float ULevelUpInfo::GetXPPercent(bool& Success, int32 CurrentXP) const
{
	float XPPercent = 100.0f;
	
	const int32 CurrentLevel = FindLevelForXP(CurrentXP);
	
	if (IsValidLevel(CurrentLevel))
	{
		const int32 LevelUpRequirement = LevelUpInformation[CurrentLevel].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInformation[CurrentLevel -1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = CurrentXP - PreviousLevelUpRequirement;

		Success = true;
		return float(XPForThisLevel) / float(DeltaLevelRequirement);	
	}
	Success = false;
	return XPPercent;
}

const FAuraLevelUpInfo& ULevelUpInfo::GetLevelUpInfoForLevel(int32 Level) const
{
	if (IsValidLevel(Level))
	{
		return LevelUpInformation[Level];
	}
    static const FAuraLevelUpInfo DefaultLevelUpInfo;
	return DefaultLevelUpInfo;
}

bool ULevelUpInfo::IsValidLevel(int32 Level) const
{
	const int32 MaxLevel = LevelUpInformation.Num() - 1;
	if (Level <= MaxLevel && Level > 0)
		return true;
	return false;
}
