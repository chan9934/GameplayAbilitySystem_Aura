// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESaveSlotStatus : uint8
{
	Vacant,
	EnterName,
	Taken
};

USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ClassDefaults")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityStatus = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilitySlot = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityType = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel;

	bool operator==(const FSavedAbility& other)const
	{
		return (GameplayAbility == other.GameplayAbility) &&( AbilityTag == other.AbilityTag) && (AbilityStatus == other.AbilityStatus) && (AbilitySlot == other.AbilitySlot) && (AbilityType == other.AbilityType) && (AbilityLevel == other.AbilityLevel);
	}
};
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString SlotName = FString();
	UPROPERTY()
	int32 SlotIndex = 0;
	UPROPERTY()
	FString PlayerName = FString("Defualt Name");
	UPROPERTY()
	FString MapName = FString("Defualt Map Name");
	UPROPERTY()
	FName PlayerStartTag;
	UPROPERTY()
	bool bFirstTimeLoadIn = true;
	
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus = ESaveSlotStatus::Vacant;

	/*
	 * Player
	 */
	UPROPERTY()
	int32 PlayerLevel = 1;

	UPROPERTY()
	int32 XP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;
	
	UPROPERTY()
	float Strength = 0;
	UPROPERTY()
	float Intelligence = 0;
	UPROPERTY()
	float Resilience = 0;
	UPROPERTY()
	float Vigor = 0;

	UPROPERTY()
	TArray<FSavedAbility> SavedAbilities;
	
};
