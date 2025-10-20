// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

struct FAuraLevelUpInfo;
class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/)
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointChangedDelegate;
	FOnPlayerStatChanged OnSpellPointChangedDelegate;
	
	FORCEINLINE int32 GetPlayerLevel()const { return Level;}
	FORCEINLINE int32 GetPlayerXP()const { return XP;}
	FORCEINLINE int32 GetAttributePoints()const { return AttributePoints;}
	FORCEINLINE int32 GetSpellPoints()const { return SpellPoints;}

	UFUNCTION(BlueprintCallable)
	void SetLevel(int32 NewLevel);
	UFUNCTION(BlueprintCallable)
	void SetXP(int32 NewXP);
	UFUNCTION(BlueprintCallable)
	void SetAttributePoints(int32 InPoints);
	UFUNCTION(BlueprintCallable)
	void SetSpellPoints(int32 InPoints);
	
	UFUNCTION(BlueprintCallable)
	void AddToLevel(int32 AddLevel);
	UFUNCTION(BlueprintCallable)
	void AddToXP(int32 AddXP);
	UFUNCTION(BlueprintCallable)
	void AddToAttributePoints(int32 InPoints);
	UFUNCTION(BlueprintCallable)
	void AddToSpellPoints(int32 InPoints);
	
	UFUNCTION(BlueprintCallable)
	int32 FindLevelForXP(int InXP)const;
	
	UFUNCTION(BlueprintCallable)
	float GetXPPercent(bool& Success, int32 CurrentXP)const;
	
	
	UFUNCTION(BlueprintPure)
	ULevelUpInfo* GetLevelUpInfo()const;

	const FAuraLevelUpInfo& GetAuraLevelInfo(int32 InLevel)const;


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 0;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints)
	int32 AttributePoints = 0;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints)
	int32 SpellPoints = 0;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);
	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
	
};
