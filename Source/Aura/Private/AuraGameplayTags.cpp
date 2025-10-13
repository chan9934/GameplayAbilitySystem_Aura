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
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.HealthRegeneration"), TEXT("Amount of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.ManaRegeneration"), TEXT("Amount of Mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.MaxHealth"), TEXT("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Secondary.MaxMana"), TEXT("Maximum amount of Mana obtainable"));

	
	/*
	 * Input Tags
	 */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.LMB"), TEXT("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.RMB"), TEXT("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.1"), TEXT("Input Tag for 1 key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.2"), TEXT("Input Tag for 2 key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.3"), TEXT("Input Tag for 3 key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.4"), TEXT("Input Tag for 4 key"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.Passive.1"), TEXT("Input Tag Passive Ability 1"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("InputTag.Passive.2"), TEXT("Input Tag Passive Ability 2"));
	
	/*
	 * Damage Types
	 */
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage"), TEXT("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Fire"), TEXT("Fire Damage Type"));
	GameplayTags.Damage_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Lighting"), TEXT("Lighting Damage Type"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Arcane"), TEXT("Arcane Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Damage.Physical"), TEXT("Physical Damage Type"));

	/*
	 * Meta Attributes
	 */

	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Meta.IncomingXP"), TEXT("Incoming XP Meta Attribute"));
	
	/*
	 * Resistances
	 */

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Fire"), TEXT("Resistance to Arcane damage"));
	GameplayTags.Attributes_Resistance_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Lighting"), TEXT("Resistance to Lighting Damage"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Arcane"), TEXT("Resistance to Arcane Damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Attributes.Resistance.Physical"), TEXT("Resistance to Physical Damage"));
	
	
	/*
	 * Debuffs
	 */

	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Burn"), TEXT("Debuff for Fire damage"));	
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Stun"), TEXT("Debuff for Lightning damage"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Arcane"), TEXT("Debuff for Arcane damage"));
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Physical"), TEXT("Debuff for Physical damage"));

	GameplayTags.Debuff_Change = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Change"), TEXT("Debuff Change"));	
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Damage"), TEXT("Debuff Damage"));
	GameplayTags.Debuff_Frequency =  UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Frequency"), TEXT("Debuff Frequency"));
	GameplayTags.Debuff_Duration =   UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Debuff.Duration"), TEXT("Debuff Duration"));
	
	/*
	 * Map of Damage Types to Resistances
	 */
	
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Lighting, GameplayTags.Attributes_Resistance_Lighting);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	
	/*
	 * Map of Damage Types to Debuffs
	 */
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lighting, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);

	/*
	 * Effects
	 */
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Effects.HitReact"), TEXT("Tag granted when hit reacting"));

	/*
	 * Abilities
	 */
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Attack"), TEXT("Attack Ability Tag"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Summon"), TEXT("Summon Ability Tag"));
	
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Fire.FireBolt"), TEXT("FireBolt Ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Lightning.Electrocute"), TEXT("Electrocute Ability Tag"));

	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Passive.LifeSiphon"), TEXT("Life Siphon"));
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Passive.ManaSiphon"), TEXT("Mana Siphon"));
	GameplayTags.Abilities_Passive_HalfOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Passive.HalfOfProtection"), TEXT("Half Of Protection"));
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.HitReact"), TEXT("Hit React Ability"));
	
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Status.Locked"), TEXT("Locked Status"));
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Status.Eligible"), TEXT("Eligible Status"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Status.Unlocked"), TEXT("Unlocked Status"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Status.Equipped"), TEXT("Equipped Status"));
	
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Type.Offensive"), TEXT("Type Offensive"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Type.Passive"), TEXT("Type Passive"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Abilities.Type.None"), TEXT("Type None"));
	/*
	 * Cooldown
	 */
	
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Cooldown.Fire.FireBolt"), TEXT("FireBolt Cooldown Tag"));

	/*
	 * Combat Sockets
	 */
	
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("CombatSocket.Weapon"), TEXT("Weapon"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("CombatSocket.LeftHand"), TEXT("Left Hand"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("CombatSocket.RightHand"), TEXT("Right Hand"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("CombatSocket.Tail"), TEXT("Tail"));
	
	/*
	 * Montages
	 */
	
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Montage.Attack.1"), TEXT("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Montage.Attack.2"), TEXT("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Montage.Attack.3"), TEXT("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Montage.Attack.4"), TEXT("Attack 4"));
	
	/*
	 * Player Tags
	 */

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Player.Block.InputPressed"), TEXT("Block Input Pressed callback for input"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Player.Block.InputHeld"), TEXT("Block Input held callback for input"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Player.Block.InputReleased"), TEXT("Block Input Released callback for input"));
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Player.Block.CursorTrace"), TEXT("Block tracing under the cursor"));
	
	
}
