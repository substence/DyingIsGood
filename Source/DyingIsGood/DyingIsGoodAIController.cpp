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
	if (StartActor && MinionClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			for (size_t i = 0; i < 2; i++)
			{
				FTransform SpawnTransform = StartActor->GetActorTransform();
				FVector SpawnLocation = SpawnTransform.GetLocation();
				const float Randomness = 500.0f;
				SpawnLocation.X += FMath::RandRange(-Randomness, Randomness);
				SpawnLocation.Y += FMath::RandRange(-Randomness, Randomness);
				SpawnTransform.SetLocation(SpawnLocation);
				FActorSpawnParameters SpawnParams;				
				ACharacter* Spawned = World->SpawnActorAbsolute<ACharacter>(MinionClass, SpawnTransform, SpawnParams);
				Possess(Spawned);

				AActor* EndActor = FindFirstTriggerWithTag(FName(TEXT("Finish")));
				if (EndActor)
				{
					UNavigationSystem* const NavSys = World->GetNavigationSystem();
					NavSys->SimpleMoveToLocation(this, EndActor->GetActorLocation());
				}
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

/*void ADyingIsGoodAIController::FindFirstTriggerWithTag(FName TagName)
{
	UWorld* const World = GetWorld();

	if (World != NULL)
	{
		World->GetTimerManager().SetTimer(TimerHandle_ReloadTimerExpired, this, &UWeapon::OnReloadTimerExpire, ReloadTime);
	}
}

void ADyingIsGoodAIController::OnReloadTimerExpire()
{
	bIsReloaded = true;
	UE_LOG(LogTemp, Warning, TEXT("Reload Complete"));
}*/


