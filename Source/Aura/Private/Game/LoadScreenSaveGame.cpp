// Copyright KimDongChan


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithMapName(const FString& InMapName)
{
	for (const FSavedMap& SavedMap: SavedMaps)
	{
		if (SavedMap.MapAssetName == InMapName)
			return SavedMap;
	}
	return FSavedMap();
}

FSavedMap& ULoadScreenSaveGame::GetSavedMapReferenceWithMapName(const FString& InMapName)
{
	for (FSavedMap& SavedMap: SavedMaps)
	{
		if (SavedMap.MapAssetName == InMapName)
			return SavedMap;
	}
	FSavedMap SavedMap;
	SavedMaps.Add(SavedMap);
	return SavedMaps.Last();
}
