// Copyright KimDongChan


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = GetActorInfo().PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(GetActorInfo().AvatarActor.Get());
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	if (OwnerCharacter && OwnerCharacter->Implements<UCombatInterface>())
	{
		const USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter);
		const FVector BeamStartLocation = Weapon->GetSocketLocation(
			ICombatInterface::Execute_TipSocketName(OwnerCharacter));
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(OwnerCharacter);
		FHitResult HitResult;
		UKismetSystemLibrary::SphereTraceSingle(OwnerCharacter, BeamStartLocation, BeamTargetLocation, 10.f,
		                                        TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None,
		                                        HitResult, true);
		if (HitResult.bBlockingHit)
		{
			MouseHitLocation = HitResult.ImpactPoint;
			MouseHitActor = HitResult.GetActor();
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	if (!IsValid(MouseHitActor))return;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerCharacter);
	ActorsToIgnore.Add(MouseHitActor);

	TArray<AActor*> OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(GetAvatarActorFromActorInfo(), OverlappingActors,
	                                                     ActorsToIgnore, 850, MouseHitActor->GetActorLocation());
	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);
	//NumAdditionalTargets = 5;
	UAuraAbilitySystemLibrary::GetClosetTargets(NumAdditionalTargets, OverlappingActors, OutAdditionalTargets,
	                                            MouseHitActor->GetActorLocation());
}

bool UAuraBeamSpell::ApplyPeriodicCostGE()
{
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(TargetASC)) return false;
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(TargetASC->GetAvatarActor());
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(CostGameplayEffectClass, GetAbilityLevel(),
	                                                                   ContextHandle);
	TargetASC->OnPeriodicGameplayEffectExecuteDelegateOnSelf.AddUObject(
		this, &UAuraBeamSpell::OnPeriodicGameplayEffectExecute);
	if (!TargetASC->CanApplyAttributeModifiers(SpecHandle.Data->Def, GetAbilityLevel(), ContextHandle))
		return false;

	CostEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return true;
}

void UAuraBeamSpell::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(TargetASC)) return;
	TargetASC->OnPeriodicGameplayEffectExecuteDelegateOnSelf.RemoveAll(this);
	if (CostEffectHandle.IsValid())
	{
		TargetASC->RemoveActiveGameplayEffect(CostEffectHandle);
	}
}

void UAuraBeamSpell::OnPeriodicGameplayEffectExecute(UAbilitySystemComponent* InASC,
                                                     const FGameplayEffectSpec& InEffectSpec,
                                                     FActiveGameplayEffectHandle EffectHandle)
{
	if (EffectHandle != CostEffectHandle) return;
	if (!InASC->CanApplyAttributeModifiers(InEffectSpec.Def, GetAbilityLevel(), InEffectSpec.GetContext()))
	{
		OnPeriodicGameplayEffectDelegate.Broadcast(false);
		if (CostEffectHandle.IsValid())
		{
			 GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(CostEffectHandle);
		}
	}
	OnPeriodicGameplayEffectDelegate.Broadcast(true);
}
