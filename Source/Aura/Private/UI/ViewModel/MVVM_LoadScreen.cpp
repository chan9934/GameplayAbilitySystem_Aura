// Copyright KimDongChan


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlots.Add(0, NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass));
	LoadSlots.Add(1, NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass));
	LoadSlots.Add(2, NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass));
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index)
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		AuraGameMode->SaveSlotData(Slot, EnteredName);
		LoadSlots[Slot]->SetPlayerName(EnteredName);
		LoadSlots[Slot]->SlotStatus = ESaveSlotStatus::Taken;
		LoadSlots[Slot]->SetMapName(AuraGameMode->DefaultMapName);
		LoadSlots[Slot]->SetPlayerLevel(1);
		LoadSlots[Slot]->PlayerStartTag = AuraGameMode->DefaultPlayerStartTag;
		LoadSlots[Slot]->InitializeSlot();
		if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance()))
		{
			AuraGameInstance->PlayerStartTag = AuraGameMode->DefaultPlayerStartTag;
			AuraGameInstance->LoadSlotIndex = Slot;
			AuraGameInstance->LoadSlotName = AAuraGameModeBase::GetSlotNameWithIndex(Slot);
		}
	}
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
	SlotSelected.Broadcast();
	for (const TPair<int32, TObjectPtr<UMVVM_LoadSlot>>& LoadSlot : LoadSlots)
	{
		if (LoadSlot.Key == Slot)
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(false);
		}
		else
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);
		}
	}
	SelectedSlotIndex = Slot;
}

void UMVVM_LoadScreen::DeleteButtonPressed()
{
	if (SelectedSlotIndex != INDEX_NONE)
	{
		AAuraGameModeBase::DeleteSlot(SelectedSlotIndex);
		LoadSlots[SelectedSlotIndex]->SlotStatus = ESaveSlotStatus::Vacant;
		LoadSlots[SelectedSlotIndex]->InitializeSlot();
		LoadSlots[SelectedSlotIndex]->EnableSelectSlotButton.Broadcast(true);
		SelectedSlotIndex = INDEX_NONE;
	}
}

void UMVVM_LoadScreen::PlayButtonPressed()
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance()))
		{
			AuraGameInstance->PlayerStartTag = LoadSlots[SelectedSlotIndex]->PlayerStartTag;
			AuraGameInstance->LoadSlotIndex =  SelectedSlotIndex;
			AuraGameInstance->LoadSlotName = AAuraGameModeBase::GetSlotNameWithIndex(SelectedSlotIndex);
		}
		if (SelectedSlotIndex != INDEX_NONE)
			AuraGameMode->TravelToMap(LoadSlots[SelectedSlotIndex]->GetMapName());
	}
}

void UMVVM_LoadScreen::LoadData()
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		for (const TPair<int32, TObjectPtr<UMVVM_LoadSlot>>& LoadSlot : LoadSlots)
		{
			if (ULoadScreenSaveGame* SaveObject = AuraGameMode->GetSaveSlotData(LoadSlot.Key))
			{
				const FString PlayerName = SaveObject->PlayerName;
				const FString MapName = SaveObject->MapName;
				ESaveSlotStatus SaveSlotStatus = SaveObject->SlotStatus;

				LoadSlot.Value->SetPlayerName(PlayerName);
				LoadSlot.Value->SetMapName(MapName);
				LoadSlot.Value->SlotStatus = SaveSlotStatus;
				LoadSlot.Value->PlayerStartTag = SaveObject->PlayerStartTag;
				LoadSlot.Value->SetPlayerLevel(SaveObject->PlayerLevel);
				LoadSlot.Value->InitializeSlot();
			}
		}
	}
}

void UMVVM_LoadScreen::SetEmptyString(FString InEmptyString)
{
	UE_MVVM_SET_PROPERTY_VALUE(EmptyString, InEmptyString);
}
