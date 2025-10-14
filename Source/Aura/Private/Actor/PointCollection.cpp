
#include "Actor/PointCollection.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = false;

	Pt_Center = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_Center"));
	SetRootComponent(Pt_Center);
	ImutablePts.Add(Pt_Center);
	
	Pt_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_0"));
	Pt_0->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_0);
	
	Pt_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_1"));
	Pt_1->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_1);
	
	Pt_2 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_2"));
	Pt_2->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_2);
	
	Pt_3 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_3"));
	Pt_3->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_3);
	
	Pt_4 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_4"));
	Pt_4->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_4);
	
	Pt_5 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_5"));
	Pt_5->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_5);
	
	Pt_6 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_6"));
	Pt_6->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_6);
	
	Pt_7 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_7"));
	Pt_7->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_7);
	
	Pt_8 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_8"));
	Pt_8->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_8);
	
	Pt_9 = CreateDefaultSubobject<USceneComponent>(TEXT("Pt_9"));
	Pt_9->SetupAttachment(GetRootComponent());
	ImutablePts.Add(Pt_9);

}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 NumPoints,
	float YawOverride)
{
	checkf(ImutablePts.Num() >= NumPoints, TEXT("Attempted to access immutable points out of bounds."));

	TArray<USceneComponent*> ArrayCopy;

	for (USceneComponent* Pt : ImutablePts)
	{
		if (ArrayCopy.Num() >= NumPoints)break;

		if (Pt != Pt_Center)
		{
			FVector ToPoint = Pt->GetComponentLocation() - Pt_Center->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(Pt_Center->GetComponentLocation() + ToPoint);
		}

		const FVector RasiedLocation = Pt->GetComponentLocation() + FVector(0.f, 0.f, 500.f);
		const FVector LoweredLocation = Pt->GetComponentLocation() - FVector(0.f, 0.f, 500.f);

		TArray<AActor*> IgnoredActors;
		UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(this, IgnoredActors, TArray<AActor*>(), 1500.f, GetActorLocation());

		FHitResult HitResult;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoredActors);
		GetWorld()->LineTraceSingleByProfile(HitResult, RasiedLocation, LoweredLocation, FName("BlockALl"), QueryParams);

		if (HitResult.bBlockingHit)
		{
			Pt->SetWorldLocation(HitResult.ImpactPoint);
			Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));
		}
		ArrayCopy.Add(Pt);
	}
	return ArrayCopy;
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

