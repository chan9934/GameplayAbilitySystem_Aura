// Copyright KimDongChan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
struct FInputActionValue;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	TScriptInterface<IEnemyInterface>LastActor;
	TScriptInterface<IEnemyInterface>ThisActor;
};
