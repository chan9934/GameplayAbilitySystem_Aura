// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetcontroller(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|AttributeWidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetcontroller(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass, UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsCriticaldHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticaldHit);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayerWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);
};
