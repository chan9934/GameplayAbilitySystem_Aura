// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPeriodicGameplayEffectSignature, bool, bIsActive);
class ACharacter;
UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult);
	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();
	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation);
	UFUNCTION(BlueprintCallable)
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);
	UFUNCTION(BlueprintCallable)
	bool ApplyPeriodicCostGE();
	UPROPERTY(BlueprintAssignable)
	FOnPeriodicGameplayEffectSignature OnPeriodicGameplayEffectDelegate;
	
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	FVector MouseHitLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<AActor> MouseHitActor;
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<ACharacter> OwnerCharacter;
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	int32 MaxNumShockTargets = 5;
private:
	void OnPeriodicGameplayEffectExecute(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle EffectHandle);
	FActiveGameplayEffectHandle CostEffectHandle;
	
};
