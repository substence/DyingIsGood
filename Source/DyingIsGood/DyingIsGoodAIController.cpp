// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "DyingIsGoodAIController.h"
#include "Minion.h"

ADyingIsGoodAIController::ADyingIsGoodAIController()
{
	UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIControllerADyingIsGoodAIController"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/Minion_Blueprint'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIController found minion class"));
		MinionClass = PlayerPawnBPClass.Class;
	}
}

void ADyingIsGoodAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIControllerBeginPlay"));

	AActor* StartActor = FindFirstTriggerWithTag(FName(TEXT("Start")));
	if (StartActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIController found actor"));

		UWorld* World = GetWorld();
		if (World)
		{
			FVector SpawnLocation = StartActor->GetActorLocation();
			
			for (size_t i = 0; i < 1; i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIController spawning"));
				FActorSpawnParameters SpawnParams;				
				AActor* Spawned = World->SpawnActorAbsolute<AActor>(MinionClass, StartActor->GetActorTransform(), SpawnParams);
			}
		}
	}
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

void ADyingIsGoodAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIControllerBeginPlay"));

}

void ADyingIsGoodAIController::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
	//UE_LOG(LogTemp, Warning, TEXT("ADyingIsGoodAIControllerBeginPlay"));
}


