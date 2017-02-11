// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Minion.h"
#include "DyingIsGoodAIController.h"
#include "Runtime/Engine/Classes/Engine/TriggerBase.h"


// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();

	// Configure character movement
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true; // Rotate character to moving direction
	Movement->RotationRate = FRotator(0.f, 640.f, 0.f);
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;

	AIControllerClass = ADyingIsGoodAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SpawnDefaultController();


	FVector TargetPosition = GetActorLocation();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Finish")), FoundActors);
	for (size_t i = 0; i < FoundActors.Num(); i++)
	{
		AActor* actor = FoundActors[i];
		if (actor->Tags.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Your message"));
			//UE_LOG(LogTemp, Warning, TEXT("Your message %s"), *actor->Tags[0].ToString());
		}

		if (actor->ActorHasTag(FName(TEXT("Finish"))))
		{
			TargetPosition = actor->GetActorLocation();
		}
	}

	/*FVector TargetPosition = GetActorLocation();
	const float distance = 1000.0f;
	TargetPosition.X += FMath::FRandRange(-distance, distance);
	TargetPosition.Y += FMath::FRandRange(-distance, distance);*/
	UWorld* World = GetWorld();
	if (World)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		NavSys->SimpleMoveToLocation(Controller, TargetPosition);
	}
}

// Called every frame
void AMinion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

