// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "FieldActor.h"


// Sets default values
AFieldActor::AFieldActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFieldActor::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AFieldActor::OwnerTakesDamage);
}

void AFieldActor::OwnerTakesDamage(AActor* DamagedActor, float Damage, UDamageType const* const DamageTypeCDO, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Role >= ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("took damage on the server"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("took damage on the client"));
	}
}

// Called every frame
void AFieldActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFieldActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

