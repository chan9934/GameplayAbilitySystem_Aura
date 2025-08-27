// Copyright KimDongChan


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes Tags
	 */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Primary.Strength"), TEXT("Increases physical damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Primary.Intelligence"), TEXT("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Primary.Resilience"), TEXT("Increases Armour and Armour Penetration"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Primary.Vigor"), TEXT("Increases health"));

	/*
	 * Secondary Attributes Tags
	 */
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.Armor"), TEXT("Reduces damage taken, improves Block Change"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.ArmorPenetration"), TEXT("Ignore Percentage of enemy Armor, increases Critical Hit Chance"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.BlockChance"), TEXT("Chance to cut incoming damage in half"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.CriticalHitChance"), TEXT("Chance to double damage plus critical hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.CriticalHitDamage"), TEXT("Bonus damage added when a critical hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.CriticalHitResistance"), TEXT("Reduces Critical Hit Chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.HealthRegeneration"), TEXT("Reduces Critical Hit Chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.ManaRegeneration"), TEXT("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.MaxHealth"), TEXT("Amount of Mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.MaxMana"), TEXT("Maximum amount of Health obtainable"));

	
	/*
	 * Input Tags
	 */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.LMB"), TEXT("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.RMB"), TEXT("Input Tag for Right Mouse Butto"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.1"), TEXT("Input Tag for 1 key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.2"), TEXT("Input Tag for 2 key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.3"), TEXT("Input Tag for 3 key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.4"), TEXT("Input Tag for 4 key"));
	
	/*
	 * Damage Types
	 */
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage"), TEXT("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Fire"), TEXT("Fire Damage Type"));
	GameplayTags.Damage_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Lighting"), TEXT("Lighting Damage Type"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Arcane"), TEXT("Arcane Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Physical"), TEXT("Physical Damage Type"));
	
	/*
	 * Resistances
	 */
	
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Fire"), TEXT("Resistance to Arcane damage"));
	GameplayTags.Attributes_Resistance_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Lighting"), TEXT("Resistance to Lighting Damage"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Arcane"), TEXT("Resistance to Arcane Damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Physical"), TEXT("Resistance to Physical Damage"));

	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Lighting, GameplayTags.Attributes_Resistance_Lighting);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Effects.HitReact"), TEXT("Tag granted when hit reacting"));
	
}
