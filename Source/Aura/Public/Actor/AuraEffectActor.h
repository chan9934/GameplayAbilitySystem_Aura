#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UStaticMeshComponent;

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

	UFUNCTION(BlueprintCallable)
	void SetActorLevel(float InLevel) {ActorLevel = InLevel;}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MovementSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bRotates = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float RotationRate = 45.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bSinusoidalMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SineAmplitude = 16.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SinePeriod = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	bool bUseStartTimeline = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	float SpawnApex = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	TObjectPtr<UCurveFloat> TimelineCurve_Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	TObjectPtr<UCurveFloat> TimelineCurve_Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	TObjectPtr<USoundBase> SpawnSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	TObjectPtr<USoundBase> ConsumeSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Movement")
	TObjectPtr<USoundBase> GroumdImpactSound;
	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();
	UFUNCTION(BlueprintCallable)
	void StartRotation();

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	bool bDestroyOnEffectApplication = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applided Effects")
	bool bApplyEffectsToEnemies = false;

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
private:
	float RunningTime = 0.f;
	void ItemMovement(float DeltaTime);
	bool bCanMove = false;

	/* Timeline */
	FTimeline StartTimeline;
	UFUNCTION()
	void OnUpdatedTimeline_Location(float Output);
	UFUNCTION()
	void OnUpdatedTimeline_Scale(float Output);
	UFUNCTION()
	void OnFinishedTimeline();

	bool bHasPlayedImpactSound = false;
};
