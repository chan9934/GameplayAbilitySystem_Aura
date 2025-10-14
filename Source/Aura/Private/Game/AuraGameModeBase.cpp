// Copyright KimDongChan


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Aura/Aura.h"
#include "Components/BrushComponent.h"
#include "Engine/BlockingVolume.h"

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetBlockingVolumeCollisionSetting();
}

void AAuraGameModeBase::SetBlockingVolumeCollisionSetting()
{
	for (TActorIterator<ABlockingVolume> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->GetBrushComponent()->SetCollisionResponseToChannel(ECC_ExecludePlayers, ECR_Ignore);
	}

}
