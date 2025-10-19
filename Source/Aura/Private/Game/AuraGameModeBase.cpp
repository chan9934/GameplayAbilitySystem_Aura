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
	SetBlockingVolumeCollisionSetting();
}

void AAuraGameModeBase::SaveSlotData(const FString& SlotName, int32 SlotIndex, const FString& PlayerName)
{
	FString NewSlotName = FString::Printf(TEXT("%s_%d"), *SlotName, SlotIndex);
	if (UGameplayStatics::DoesSaveGameExist(NewSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(NewSlotName, SlotIndex);
	}
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	if(ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject))
	{
		LoadScreenSaveGame->PlayerName = PlayerName;
		LoadScreenSaveGame->SlotName = NewSlotName;
		LoadScreenSaveGame->SlotIndex = SlotIndex;

		UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, NewSlotName, SlotIndex);
	}
}

void AAuraGameModeBase::SetBlockingVolumeCollisionSetting()
{
	for (TActorIterator<ABlockingVolume> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->GetBrushComponent()->SetCollisionResponseToChannel(ECC_ExecludePlayers, ECR_Ignore);
	}
}
