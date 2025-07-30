// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo))return;

	ICombatInterface* CombatInterface =  Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);

	// ToDo : Set the Projectile Rotaion
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
	                                                Cast<APawn>(GetOwningActorFromActorInfo()),
	                                                ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// ToDo : Give the PRojectile a Gameplay Effect Spec for causing Damage.
	
	Projectile->FinishSpawning(SpawnTransform);
}
