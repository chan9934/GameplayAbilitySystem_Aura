// Copyright KimDongChan


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlots[0] = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlots[1] = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlots[2] = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index)
{
	return LoadSlots.FindChecked(Index);
}
