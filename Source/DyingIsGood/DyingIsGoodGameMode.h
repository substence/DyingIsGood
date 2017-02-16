// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "Throne.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "DyingIsGoodGameMode.generated.h"

UCLASS()
class ADyingIsGoodGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADyingIsGoodGameMode();
	virtual void InitGameState() override;
	virtual void Tick(float DeltaTime) override;
	UHealthComponent * GetHealthComponentFromActor(AActor * Actor);
	class UClass* MinionClass;
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;
	virtual void BeginPlay() override;

private:
	float TimeOfLastDeploy;
	float DeployDelay = 5.0f;
	FTransform SpawnPoint;
	FTransform TargetPoint;
	void SpawnMinion(FTransform Start, FVector End);
	AActor* FindFirstTriggerWithTag(FName Name);
	AThrone* Throne;
	UProgressBar* CharacterProgressBar;
	UProgressBar* ThroneProgressBar;
	ACharacter* Character;
};



