// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Tower.h"


// Sets default values
ATower::ATower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	/*if (Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATower has controller"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATower doesnt have a controller"));

	}*/
}

// Called every frame
void ATower::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

