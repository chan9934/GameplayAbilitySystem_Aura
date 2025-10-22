// Copyright KimDongChan


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Aura/Aura.h"
#include "Aura/AuraLogChannels.h"
#include "Components/BrushComponent.h"
#include "Engine/BlockingVolume.h"
#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/SaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == AuraGameInstance->PlayerStartTag)
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		return SelectedActor;
	}

	return nullptr;
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefualtMap);
	SetBlockingVolumeCollisionSetting();
}

void AAuraGameModeBase::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
	NewPlayer->SetControlRotation(FRotator::ZeroRotator);
}

void AAuraGameModeBase::SaveSlotData(int32 SlotIndex, const FString& MapName, const FString& PlayerName)
{
	DeleteSlot(SlotIndex);
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	if (ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject))
	{
		LoadScreenSaveGame->PlayerName = PlayerName;
		LoadScreenSaveGame->MapName = MapName;
		LoadScreenSaveGame->SlotName = NewSlotName;
		LoadScreenSaveGame->SlotIndex = SlotIndex;
		LoadScreenSaveGame->PlayerStartTag = DefaultPlayerStartTag;
		LoadScreenSaveGame->SlotStatus = ESaveSlotStatus::Taken;

		UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, NewSlotName, SlotIndex);
	}
}

void AAuraGameModeBase::DeleteSlot(int32 SlotIndex)
{
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	if (UGameplayStatics::DoesSaveGameExist(NewSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(NewSlotName, SlotIndex);
	}
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(int32 SlotIndex) const
{
	FString NewSlotName = GetSlotNameWithIndex(SlotIndex);
	if (UGameplayStatics::DoesSaveGameExist(NewSlotName, SlotIndex))
	{
		return Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(NewSlotName, SlotIndex));
	}
	return nullptr;
}

ULoadScreenSaveGame* AAuraGameModeBase::RetrieveInGameSaveData()
{
	if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		const int32 InGameLoadSlotIndex = AuraGameInstance->LoadSlotIndex;
		return GetSaveSlotData(InGameLoadSlotIndex);
	}
	return nullptr;
}

void AAuraGameModeBase::SaveInGameProgressData(ULoadScreenSaveGame* SaveObject)
{
	if (UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		const int32 InGameLoadSlotIndex = AuraGameInstance->LoadSlotIndex;
		const FString InGameLoadSlotName = AuraGameInstance->LoadSlotName;
		AuraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;
		UGameplayStatics::SaveGameToSlot(SaveObject, InGameLoadSlotName, InGameLoadSlotIndex);
	}
}

void AAuraGameModeBase::SaveWorldState(UWorld* World, const FString& DestinationMapAssetName)const
{
	FString WorldName = World->GetName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	if (UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGI->LoadSlotIndex))
		{
			if (!DestinationMapAssetName.IsEmpty())
			{
				SaveGame->MapAssetName = DestinationMapAssetName;
				SaveGame->MapName = GetMapNameFromMapAssetName(DestinationMapAssetName);
			}
			FSavedMap& SavedMap = SaveGame->GetSavedMapReferenceWithMapName(WorldName);
			if (!SavedMap.IsValid())
			{
				SavedMap.MapAssetName = WorldName;
			}
			SavedMap.SavedActors.Empty();

			for (FActorIterator Itr(World); Itr; ++Itr)
			{
				AActor* Actor = *Itr;
				//UE_LOG(LogAura, Warning, TEXT("SAveTest  Name : %s"), *GetNameSafe(Actor));
				if (!IsValid(Actor) || !Actor->Implements<USaveInterface>())continue;
				FSavedActor SavedActor;
				SavedActor.ActorName = Actor->GetFName();
				SavedActor.Transform = Actor->GetTransform();

				FMemoryWriter MemoryWriter(SavedActor.Bytes);

				FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
				Archive.ArIsSaveGame = true;

				Actor->Serialize(Archive);

				SavedMap.SavedActors.Add(SavedActor);
			}
			UGameplayStatics::SaveGameToSlot(SaveGame, AuraGI->LoadSlotName, AuraGI->LoadSlotIndex);
		}
	}
}

void AAuraGameModeBase::LoadWorldState(UWorld* World)const
{
	FString WorldName = World->GetName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	if (UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		if (!UGameplayStatics::DoesSaveGameExist(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex))return;
		ULoadScreenSaveGame* SaveGame = Cast<ULoadScreenSaveGame>(
			UGameplayStatics::LoadGameFromSlot(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex));
		if (SaveGame == nullptr)
		{
			UE_LOG(LogAura, Error, TEXT("Failed to load slot"));
			return;
		}
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>())continue;

			const FSavedMap& SavedMap = SaveGame->GetSavedMapReferenceWithMapName(WorldName);

			for (const FSavedActor& SavedActor : SavedMap.SavedActors)
			{
				if (SavedActor.ActorName != Actor->GetFName())continue;

				FMemoryReader MemoryReader(SavedActor.Bytes);
				FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
				Archive.ArIsSaveGame = true;

				Actor->Serialize(Archive);

				if (ISaveInterface::Execute_ShouldLoadTransform(Actor))
				{
					Actor->SetActorTransform(SavedActor.Transform);
				}
					ISaveInterface::Execute_LoadActor(Actor);
			}
		}
	}
}

void AAuraGameModeBase::TravelToMap(const FString& MapName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Maps.FindChecked(MapName));
}

void AAuraGameModeBase::SetBlockingVolumeCollisionSetting()
{
	for (TActorIterator<ABlockingVolume> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->GetBrushComponent()->SetCollisionResponseToChannel(ECC_ExecludePlayers, ECR_Ignore);
	}
}

FString AAuraGameModeBase::SlotName = FString("LoadSlot");

FString AAuraGameModeBase::GetSlotNameWithIndex(int32 SlotIndex)
{
	return FString::Printf(TEXT("%s_%d"), *SlotName, SlotIndex);
}

FString AAuraGameModeBase::GetMapNameFromMapAssetName(const FString& MapAssetName)const
{
	for (auto& Map : Maps)
	{
		if (Map.Value.ToSoftObjectPath().GetAssetName() == MapAssetName)
		{
			return Map.Key;
		}
	}
	return FString();
}
