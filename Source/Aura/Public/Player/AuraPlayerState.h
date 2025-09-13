// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32)
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
	FOnPlayerStatChanged OnLevelChangedDelegate;
	
	FORCEINLINE int32 GetPlayerLevel()const { return Level;}
	FORCEINLINE int32 GetPlayerXP()const { return XP;}

	UFUNCTION(BlueprintCallable)
	void SetLevel(int NewLevel);
	UFUNCTION(BlueprintCallable)
	void AddToLevel(int AddLevel);
	UFUNCTION(BlueprintCallable)
	void SetXP(int NewXP);
	UFUNCTION(BlueprintCallable)
	void AddToXP(int AddXP);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

	float GetXPPercent(bool& Success, int32 CurrentXP)const;

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

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
};
