// Copyright KimDongChan


#include "UI/ViewModel/MVVM_LoadScreen.h"

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
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
}
