// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

class UMVVM_LoadSlot;
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void InitializeLoadSlots();

	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelected;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(int32 Slot, const FString& EnteredName);
	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 Slot);
	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 Slot);

	void LoadData();

	void SetEmptyString(FString InEmptyString);
	FString GetEmptyString()const {return EmptyString;}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter , Getter)
	FString EmptyString;
private:
	UPROPERTY()
	TMap<int32, TObjectPtr<UMVVM_LoadSlot>> LoadSlots;

};
