// Copyright KimDongChan


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
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
