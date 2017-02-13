// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::OnRegister()
{
	Super::OnRegister();
	AActor* Owner = this->GetOwner();
	if (Owner != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthComponent::OnRegister"));

		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OwnerTakesDamage);
	}
}

void UHealthComponent::OwnerTakesDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("took damage"));

	Health -= Damage;
	if (Health <= 0.0f)
	{
		AActor* Owner = this->GetOwner();
		if (Owner != NULL)
		{
			Owner->Destroy();
		}
		//dispatch death event
	}
}

float UHealthComponent::GetHealth()
{
	return this->Health;
}

void UHealthComponent::SetHealth(float Value)
{
	this->Health = Value;
}


