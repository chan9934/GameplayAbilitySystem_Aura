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
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystem|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetcontroller(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystem|AttributeWidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetcontroller(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystem|CharacterClassDefaults")
	static void InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = WorldContextObject), Category = "AuraAbilitySystem|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);
};
