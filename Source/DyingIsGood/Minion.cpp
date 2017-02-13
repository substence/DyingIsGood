// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "HealthComponent.h"
#include "Minion.h"
#include "DyingIsGoodAIController.h"
#include "Runtime/Engine/Classes/Engine/TriggerBase.h"


// Sets default values
AMinion::AMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Health->SetHealth(10.0f);
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
}

// Called every frame
void AMinion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	DamageAllNearbyActors();
}

void AMinion::DamageAllNearbyActors()
{
	TArray<AActor*> Touching;
	GetCapsuleComponent()->GetOverlappingActors(Touching);
	for (size_t i = 0; i < Touching.Num(); i++)
	{
		AActor* Actor = Touching[i];
		if (!Actor->IsA(AMinion::StaticClass()))
		{
			DamageActor(Actor);
		}
	}
}

void AMinion::DamageActor(AActor* Actor)
{
	if (Actor->IsA(AMinion::StaticClass()))
	{
		return;
	}
	if (Actor && (Health->GetHealth() != 0.f))
	{
		UE_LOG(LogTemp, Warning, TEXT("doing damage %s"), *Actor->GetFName().ToString());
	}
	FPointDamageEvent PointDmg;
	UGameplayStatics::ApplyDamage(Actor, Health->GetHealth(), Controller, this, UDamageType::StaticClass());
	//Actor->TakeDamage(Health->GetHealth(), PointDmg, Controller, this);
	//UE_LOG(LogTemp, Warning, TEXT("hit and actor %s"), *Actor->GetFName().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("attacking for is %f"), Health->GetHealth());

	Destroy();
	//Actor->TakeDamage(Health->GetHealth(), , this->Controller, this);
}
