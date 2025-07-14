#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	TArray<TSubclassOf<UGameplayEffect>>  DurationGameplayEffectClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy= EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy= EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	float ActorLevel = 1.f;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, TObjectPtr<UAbilitySystemComponent>> ActiveEffectHandles;
};
