// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Throne.h"
#include "HealthComponent.h"


// Sets default values
AThrone::AThrone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Health->SetMaxHealth(100.0f);
	Health->SetHealth(100.0f);
}

// Called when the game starts or when spawned
void AThrone::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AThrone::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

