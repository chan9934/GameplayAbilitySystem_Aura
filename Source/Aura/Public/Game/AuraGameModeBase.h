// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;
class USaveGame;
class ULoadScreenSaveGame;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	void SaveSlotData(int32 SlotIndex, const FString& PlayerName);
	ULoadScreenSaveGame* GetSaveSlotData(int32 SlotIndex)const;
protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

private:
	void SetBlockingVolumeCollisionSetting();
	FString SlotName = FString("LoadSlot");
	FString GetSlotNameWithIndex(int32 SlotIndex)const;
};
