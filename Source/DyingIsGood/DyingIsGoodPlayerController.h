// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Public/Actors/FieldActor.h"
#include "Public/PlayerIdentity.h"
#include "DyingIsGoodPlayerController.generated.h"

UCLASS()
class ADyingIsGoodPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADyingIsGoodPlayerController();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFieldActor> FieldActorToSpawn;

	UPROPERTY(Replicated)
	int TeamIndex = -1;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	void StartSpawnFieldActorAtMouse();

	UFUNCTION(Reliable, Server, WithValidation)
	void SpawnFieldActorAtMouse(FVector_NetQuantize ImpactPoint);

	void SpawnFieldActorAtMouse_Implementation(FVector_NetQuantize ImpactPoint);

	bool SpawnFieldActorAtMouse_Validate(FVector_NetQuantize ImpactPoint);

	//FVector_NetQuantize ImpactPoint;
};


