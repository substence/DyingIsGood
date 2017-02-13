// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "DyingIsGoodAIController.h"
#include "Minion.h"

ADyingIsGoodAIController::ADyingIsGoodAIController()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/Minion_Blueprint'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		MinionClass = PlayerPawnBPClass.Class;
	}
}

void ADyingIsGoodAIController::BeginPlay()
{
	Super::BeginPlay();

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

void ADyingIsGoodAIController::Tick(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIControllerTick"));
	Super::Tick(DeltaSeconds);
	float DurationSinceLastSpawn = GetWorld()->GetTimeSeconds() - TimeOfLastDeploy;
	if (DurationSinceLastSpawn > DeployDelay)
	{
		for (size_t i = 0; i < 3; i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("deploying minion"));
			//SpawnMinion(SpawnPoint, TargetPoint.GetLocation());
		}
	}
}

void ADyingIsGoodAIController::SpawnMinion(FTransform Start, FVector End)
{
	UWorld* World = GetWorld();
	if (!MinionClass || !World)
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
	Possess(Spawned);

	AActor* EndActor = FindFirstTriggerWithTag(FName(TEXT("Finish")));
	if (!End.IsZero())
	{
		UNavigationSystem* const NavSys = World->GetNavigationSystem();
		NavSys->SimpleMoveToLocation(this, End);
	}
	TimeOfLastDeploy = World->GetTimeSeconds();
}

AActor* ADyingIsGoodAIController::FindFirstTriggerWithTag(FName TagName)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagName, FoundActors);
	if (FoundActors.Num() > 0)
	{
		return FoundActors[0];
	}
	return NULL;
}


