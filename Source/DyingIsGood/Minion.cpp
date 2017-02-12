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

	/*UStaticMeshComponent* PhysicalMesh = NewObject<UStaticMeshComponent>(this);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	PhysicalMesh->SetStaticMesh(SphereMeshAsset.Object);
	if (RootComponent)
	{
		PhysicalMesh->AttachTo(RootComponent);
	}*/
}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();

	// Configure character movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true; // Rotate character to moving direction
	Movement->RotationRate = FRotator(0.f, 640.f, 0.f);
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;

	/*AIControllerClass = ADyingIsGoodAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//Controller = GetWorld()->SpawnActor<ADyingIsGoodAIController>(GetActorLocation(), FRotator::ZeroRotator);
	*/
	SpawnDefaultController();

	if (Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("created aicontroller %s"), *Controller->GetFName().ToString());
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Finish")), FoundActors);
	if (FoundActors.Num() > 0)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			NavSys->SimpleMoveToLocation(Controller, FoundActors[0]->GetActorLocation());
		}
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

