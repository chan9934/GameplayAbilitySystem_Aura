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
	void SaveSlotData(int32 SlotIndex, const FString& MapName, const FString& PlayerName);
	static void DeleteSlot(int32 SlotIndex);
	ULoadScreenSaveGame* GetSaveSlotData(int32 SlotIndex)const;
	void TravelToMap(const FString& MapName);

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefualtMap;
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	static FString GetSlotNameWithIndex(int32 SlotIndex);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

private:
	void SetBlockingVolumeCollisionSetting();
	static FString SlotName;
};
