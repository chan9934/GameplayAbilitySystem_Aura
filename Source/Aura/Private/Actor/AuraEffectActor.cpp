#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	MovementSceneComponent = CreateDefaultSubobject<USceneComponent>("MovementSceneComponent");
	MovementSceneComponent->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(SpawnSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation());

	if (bUseStartTimeline && TimelineCurve_Location && TimelineCurve_Scale)
	{
		FOnTimelineFloat UpdateCallback_Location;
		FOnTimelineFloat UpdateCallback_Scale;
		FOnTimelineEvent FinishedCallback;

		UpdateCallback_Location.BindDynamic(this, &AAuraEffectActor::OnUpdatedTimeline_Location);
		UpdateCallback_Scale.BindDynamic(this, &AAuraEffectActor::OnUpdatedTimeline_Scale);
		FinishedCallback.BindDynamic(this, &AAuraEffectActor::OnFinishedTimeline);
		StartTimeline.AddInterpFloat(TimelineCurve_Location, UpdateCallback_Location);
		StartTimeline.AddInterpFloat(TimelineCurve_Scale, UpdateCallback_Scale);
		StartTimeline.SetTimelineFinishedFunc(FinishedCallback);
		StartTimeline.PlayFromStart();
		bCanMove = false;
	}
	else
	{
		bCanMove = true;
	}
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCanMove)
		ItemMovement(DeltaTime);

	if (bUseStartTimeline)
	{
		StartTimeline.TickTimeline(DeltaTime);
	}
}

void AAuraEffectActor::Destroyed()
{
	Super::Destroyed();
	if (IsValid(ConsumeSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConsumeSound, GetActorLocation());
}

void AAuraEffectActor::StartSinusoidalMovement()
	{
	bSinusoidalMovement = true;
}

void AAuraEffectActor::StartRotation()
{
	bRotates = true;
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (TargetASC)
		{
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;

			for (auto HandlePair : ActiveEffectHandles)
			{
				if (HandlePair.Value == TargetASC)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (auto HandlePair : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(HandlePair);
			}
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor,
                                           TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses)
{
	if (!bApplyEffectsToEnemies && TargetActor->ActorHasTag(FName("Enemy"))) return;
	check(!GameplayEffectClasses.IsEmpty());
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)return;

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	for (auto GameplayEffectClass : GameplayEffectClasses)
	{
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
			GameplayEffectClass, ActorLevel, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
			*EffectSpecHandle.Data.Get());

		if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy ==
				EGameplayEffectDurationType::Infinite;
			if (bIsInfinite)
			{
				ActiveEffectHandles.Add({ActiveEffectHandle, TargetASC});
			}
			if (bDestroyOnEffectApplication && !bIsInfinite)
				Destroy();
		}
	}
}

void AAuraEffectActor::ItemMovement(float DeltaTime)
{
	if (!IsValid(MovementSceneComponent))return;
	if (bRotates)
	{
		MovementSceneComponent->AddLocalRotation(FRotator(0, DeltaTime * RotationRate, 0));
	}
	if (bSinusoidalMovement)
	{
		if (RunningTime >= SinePeriod)
		{
			RunningTime -= SinePeriod;
		}

		float SinValue = FMath::Sin((2 * PI * RunningTime) / SinePeriod);

		RunningTime += DeltaTime;
		MovementSceneComponent->SetRelativeLocation(FVector(0, 0, SinValue * SineAmplitude));
	}
}

void AAuraEffectActor::OnUpdatedTimeline_Location(float Output)
{
	float ZValue = Output * SpawnApex;
	MovementSceneComponent->SetRelativeLocation(FVector(0, 0, ZValue));
	if (GroumdImpactSound != nullptr, !bHasPlayedImpactSound && Output < 0)
	{
		bHasPlayedImpactSound = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GroumdImpactSound, GetActorLocation());
	}
}

void AAuraEffectActor::OnUpdatedTimeline_Scale(float Output)
{
	MovementSceneComponent->SetRelativeScale3D(FVector(Output, Output, Output));
}

void AAuraEffectActor::OnFinishedTimeline()
{
	bCanMove = true;
}
