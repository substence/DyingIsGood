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
}

// Called when the game starts or when spawned
void AThrone::BeginPlay()
{
	Super::BeginPlay();
	Health->SetHealth(100.0f);
	UE_LOG(LogTemp, Warning, TEXT("adding"));

	UDamageType const* const DamageTypeCDO = GetDefault<UDamageType>();
	OnTakeAnyDamage.AddDynamic(this, &AThrone::OwnerTakesDamage);
	//OnTakeAnyDamage.Execute();
	OnTakeAnyDamage.Broadcast(this, 10.0f, DamageTypeCDO, this->GetInstigatorController(), this);
}

void AThrone::OwnerTakesDamage(AActor* DamagedActor, float Damage, UDamageType const* const DamageTypeCDO, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health->SetHealth(50.0f);
	UE_LOG(LogTemp, Warning, TEXT("took damage"));
}

float AThrone::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damagedone = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnTakeAnyDamage.Broadcast(this, damagedone, DamageEvent.ClassID, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("TakeDamage %f"), damagedone);

	return damagedone;
}

// Called every frame
void AThrone::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//UE_LOG(LogTemp, Warning, TEXT("throne health is %f"), Health->GetHealth());
}

