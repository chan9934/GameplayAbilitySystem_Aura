// Copyright KimDongChan


#include "UI/ViewModel/MVVM_LoadScreen.h"

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
		LoadSlots[Slot]->InitializeSlot();
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

void UMVVM_LoadScreen::LoadData()
{
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		for (const TPair<int32, TObjectPtr<UMVVM_LoadSlot>>& LoadSlot : LoadSlots)
		{
			if (ULoadScreenSaveGame* SaveObject = AuraGameMode->GetSaveSlotData(LoadSlot.Key))
			{
				const FString PlayerName = SaveObject->PlayerName;
				ESaveSlotStatus SaveSlotStatus = SaveObject->SlotStatus;

				LoadSlot.Value->SetPlayerName(PlayerName);
				LoadSlot.Value->SlotStatus = SaveSlotStatus;
				LoadSlot.Value->InitializeSlot();
			}
		}
	}
}

void UMVVM_LoadScreen::SetEmptyString(FString InEmptyString)
{
	UE_MVVM_SET_PROPERTY_VALUE(EmptyString, InEmptyString);
}
