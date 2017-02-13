// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DyingIsGood.h"
#include "DyingIsGoodGameMode.h"
#include "DyingIsGoodPlayerController.h"
#include "DyingIsGoodCharacter.h"
#include "DyingIsGoodAIController.h"
#include "DyingIsGoodGameState.h"
#include "Minion.h"

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

	static ConstructorHelpers::FClassFinder<APawn> MinionBPClass(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/Minion_Blueprint'"));
	if (MinionBPClass.Class != NULL)
	{
		MinionClass = MinionBPClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("found minion class"));
	}

	PrimaryActorTick.bCanEverTick = true;

	//GameStateClass = ADyingIsGoodGameState::StaticClass();
}

void ADyingIsGoodGameMode::InitGameState()
{
	//UE_LOG(LogTemp, Warning, TEXT("InitGameState %s"), *GameState->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("InitGameState %s"), *GameStateClass->GetName());
	Super::InitGameState();
	UWorld* World = GetWorld();
	if (World)
	{
		GetWorld()->SpawnActor<ADyingIsGoodAIController>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	AActor* StartActor = FindFirstTriggerWithTag(FName(TEXT("Start")));
	if (StartActor)
	{
		SpawnPoint = StartActor->GetActorTransform();
	}
	AActor* EndActor = FindFirstTriggerWithTag(FName(TEXT("Finish")));
	if (EndActor)
	{
		TargetPoint = EndActor->GetActorTransform();
	}
}

void ADyingIsGoodGameMode::SpawnMinion(FTransform Start, FVector End)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	FVector SpawnLocation = Start.GetLocation();
	const float Randomness = 500.0f;
	SpawnLocation.X += FMath::RandRange(-Randomness, Randomness);
	SpawnLocation.Y += FMath::RandRange(-Randomness, Randomness);
	Start.SetLocation(SpawnLocation);
	FActorSpawnParameters SpawnParams;
	ACharacter* Spawned = World->SpawnActorAbsolute<ACharacter>(MinionClass, Start, SpawnParams);

	AActor* EndActor = FindFirstTriggerWithTag(FName(TEXT("Finish")));
	if (!End.IsZero())
	{
		UNavigationSystem* const NavSys = World->GetNavigationSystem();
		NavSys->SimpleMoveToLocation(Spawned->GetController(), End);
	}
	TimeOfLastDeploy = World->GetTimeSeconds();
}

AActor* ADyingIsGoodGameMode::FindFirstTriggerWithTag(FName TagName)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagName, FoundActors);
	if (FoundActors.Num() > 0)
	{
		return FoundActors[0];
	}
	return NULL;
}

void ADyingIsGoodGameMode::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("ticking"));
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("ticking"));

	UWorld* World = GetWorld();
	float DurationSinceLastSpawn = GetWorld()->GetTimeSeconds() - TimeOfLastDeploy;
	if (DurationSinceLastSpawn > DeployDelay)
	{
		for (size_t i = 0; i < 3; i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("deploying minion"));
			SpawnMinion(SpawnPoint, TargetPoint.GetLocation());
		}
	}
}
