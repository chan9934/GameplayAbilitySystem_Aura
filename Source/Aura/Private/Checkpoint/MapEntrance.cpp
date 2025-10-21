// Copyright KimDongChan


#include "Checkpoint/MapEntrance.h"

#include "Components/SphereComponent.h"
#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Sphere->SetupAttachment(MoveToComponent);
}

void AMapEntrance::LoadActor_Implementation()
{
}

void AMapEntrance::HighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(true);
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;
		if (AAuraGameModeBase* AuraGM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			if (UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(AuraGM->GetGameInstance()))
			{
				ULoadScreenSaveGame* SaveObject = AuraGM->GetSaveSlotData(AuraGI->LoadSlotIndex);
			}
				const FString MapAssetName = DestinationMap.ToSoftObjectPath().GetAssetName();
			AuraGM->SaveWorldState(GetWorld(), MapAssetName);
			IPlayerInterface::Execute_SaveProgress(OtherActor, DestinationPlayerStartTag);
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
		}
	}
}
