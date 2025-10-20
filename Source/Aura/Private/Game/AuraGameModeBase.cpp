// Copyright KimDongChan


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Aura/Aura.h"
#include "Components/BrushComponent.h"
#include "Engine/BlockingVolume.h"
#include "Game/LoadScreenSaveGame.h"
#include "Kismet/GameplayStatics.h"

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefualtMap);
	SetBlockingVolumeCollisionSetting();
}

void AAuraGameModeBase::SaveSlotData(int32 SlotIndex, const FString& MapName, const FString& PlayerName)
{
	DeleteSlot(SlotIndex);
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	if (ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject))
	{
		LoadScreenSaveGame->PlayerName = PlayerName;
		LoadScreenSaveGame->MapName = MapName;
		LoadScreenSaveGame->SlotName = NewSlotName;
		LoadScreenSaveGame->SlotIndex = SlotIndex;
		LoadScreenSaveGame->SlotStatus = ESaveSlotStatus::Taken;

		UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, NewSlotName, SlotIndex);
	}
}

void AAuraGameModeBase::DeleteSlot(int32 SlotIndex)
{
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	if (UGameplayStatics::DoesSaveGameExist(NewSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(NewSlotName, SlotIndex);
	}
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(int32 SlotIndex) const
{
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	if (UGameplayStatics::DoesSaveGameExist(NewSlotName, SlotIndex))
	{
		return Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(NewSlotName, SlotIndex));
	}
	return nullptr;

}

void AAuraGameModeBase::TravelToMap(const FString& MapName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Maps.FindChecked(MapName));
}

void AAuraGameModeBase::SetBlockingVolumeCollisionSetting()
{
	for (TActorIterator<ABlockingVolume> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->GetBrushComponent()->SetCollisionResponseToChannel(ECC_ExecludePlayers, ECR_Ignore);
	}
}

FString AAuraGameModeBase::SlotName = FString("LoadSlot");

FString AAuraGameModeBase::GetSlotNameWithIndex(int32 SlotIndex)
{
	return FString::Printf(TEXT("%s_%d"), *SlotName, SlotIndex);
}
