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
	static void DeleteSlot(int32 SlotIndex);
	ULoadScreenSaveGame* GetSaveSlotData(int32 SlotIndex)const;
	ULoadScreenSaveGame* RetrieveInGameSaveData();
	void SaveInGameProgressData(ULoadScreenSaveGame* SaveObject);
	void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString())const;
	void LoadWorldState(UWorld* World)const;
	void TravelToMap(const FString& MapName);

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	static FString GetSlotNameWithIndex(int32 SlotIndex);
	FString GetMapNameFromMapAssetName(const FString& MapAssetName)const;

	void PlayerDied(ACharacter* DeadCharacter);
protected:
	virtual void BeginPlay() override;
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

private:
	void SetBlockingVolumeCollisionSetting();
	static FString SlotName;
};
