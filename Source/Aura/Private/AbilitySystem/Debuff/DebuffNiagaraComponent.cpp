// Copyright KimDongChan


#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aura/AuraLogChannels.h"
#include "Interaction/CombatInterface.h"

UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	bAutoActivate = false;
}

void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner());
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
		{
			ASC->RegisterGameplayTagEvent(DebuffTag, EGameplayTagEventType::NewOrRemoved).AddUObject(
				this, &UDebuffNiagaraComponent::DebuffTagChanged);
		}
		else if (CombatInterface)
		{
			CombatInterface->GetOnASCRegisteredDelegate().AddWeakLambda(this,
			                                                            [this](UAbilitySystemComponent* InASC)
			                                                            {
				                                                            InASC->RegisterGameplayTagEvent(
						                                                            DebuffTag,
						                                                            EGameplayTagEventType::NewOrRemoved)
					                                                            .
					                                                            AddUObject(
						                                                            this,
						                                                            &UDebuffNiagaraComponent::DebuffTagChanged);
			                                                            });
		}
		if (CombatInterface)
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UDebuffNiagaraComponent::OnOnwerDeath);
		}
	}
}

void UDebuffNiagaraComponent::DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (CallbackTag == DebuffTag)
	{
		const bool bOwnerValid = IsValid(GetOwner());
		const bool bOwnerAlibe = (GetOwner()->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(GetOwner()));
		if (NewCount > 0 && (bOwnerValid && !bOwnerAlibe))
		{
			Activate();
		}
		else
		{
			Deactivate();
		}
	}
}

void UDebuffNiagaraComponent::OnOnwerDeath(AActor* DeadActor)
{
	Deactivate();
}
