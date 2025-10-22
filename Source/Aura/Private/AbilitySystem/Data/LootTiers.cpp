// Copyright KimDongChan


#include "AbilitySystem/Data/LootTiers.h"

TArray<FLootItem> ULootTiers::GetLootItems()
{
	TArray<FLootItem> ReturnItmes;
	
	for (const FLootItem& LootItem : LootItems)
	{
		for (int32 i = 0; i < LootItem.MaxNumberToSpawn; ++i)
		{
			if (FMath::FRandRange(1.f, 100.f) < LootItem.ChanceToSpawn)
			{
				FLootItem NewItem = FLootItem(LootItem.LootClass, LootItem.bLootLevelOverride);
				ReturnItmes.Add(NewItem);
			}
		}
	}
	return ReturnItmes;
}
