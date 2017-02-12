// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DyingIsGood.h"
#include "DyingIsGoodGameMode.h"
#include "DyingIsGoodPlayerController.h"
#include "DyingIsGoodCharacter.h"
#include "DyingIsGoodAIController.h"

ADyingIsGoodGameMode::ADyingIsGoodGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADyingIsGoodPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADyingIsGoodGameMode::InitGameState()
{
	Super::InitGameState();
	UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodGameModeInitGameState"));
	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->SpawnActor<ADyingIsGoodAIController>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
}
