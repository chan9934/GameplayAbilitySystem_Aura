#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()

public:
	AAuraProjectile();
	
	FDamageEffectParams DamageEffectParams;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
    UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;
	UPROPERTY(EditDefaultsOnly)
	float MinDistancePerFrame = 10.f;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void OnHit();
	virtual void Destroyed() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	bool bHit = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent ;

	FVector LocationThisFrame;
	FVector LocationLastFrame;
	
};
