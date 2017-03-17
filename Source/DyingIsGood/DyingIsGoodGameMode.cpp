// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DyingIsGood.h"
#include "DyingIsGoodGameMode.h"
#include "DyingIsGoodPlayerController.h"
#include "DyingIsGoodCharacter.h"
#include "DyingIsGoodAIController.h"
#include "DyingIsGoodGameState.h"
#include "Minion.h"
#include "Engine.h"
#include "ProgressBar.h"
#include "Blueprint/UserWidget.h"

ADyingIsGoodGameMode::ADyingIsGoodGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = PlayerControllerBlueprint;
	PrimaryActorTick.bCanEverTick = true;
}

void ADyingIsGoodGameMode::InitGameState()
{
	Super::InitGameState();
}

void ADyingIsGoodGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADyingIsGoodGameMode::BeginPlay()
{
	Super::BeginPlay();
}

FString ADyingIsGoodGameMode::InitNewPlayer
(
	APlayerController * NewPlayerController,
	const FUniqueNetIdRepl & UniqueId,
	const FString & Options,
	const FString & Portal
)
{
	FString Dunno = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	UPlayerIdentity* PlayerIdentity = NewObject<UPlayerIdentity>();
	PlayerIdentity->TeamIndex = Players.Num();
	PlayerIdentity->Controller = NewPlayerController;
	Players.Add(PlayerIdentity);

	ADyingIsGoodPlayerController* Controller = Cast<ADyingIsGoodPlayerController>(NewPlayerController);
	if (Controller)
	{
		Controller->Identity = PlayerIdentity;
		Controller->test = PlayerIdentity->TeamIndex;
		UE_LOG(LogTemp, Warning, TEXT("identity is set %d"), Controller->test);
		if (Controller->Identity)
		{
			//UE_LOG(LogTemp, Warning, TEXT("identity is valid"));

		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("played joined %d"), PlayerIdentity->TeamIndex);

	TArray<AFieldActor*> Actors;
	for (TActorIterator<AFieldActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->TeamIndex == PlayerIdentity->TeamIndex)
		{
			//UE_LOG(LogTemp, Warning, TEXT("assigning player to actor %d"), PlayerIdentity->TeamIndex);

			ActorItr->Identity = PlayerIdentity;
		}
	}
	return Dunno;
}
