// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//UE_LOG(LogTemp, Warning, TEXT("HealthComponentUHealthComponent"));

	// ...
}

void UHealthComponent::OnRegister()
{
	Super::OnRegister();
	AActor* Owner = this->GetOwner();
	//UE_LOG(LogTemp, Warning, TEXT("HealthComponent attemtping regi"));

	if (Owner != NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthComponentOnRegister"));

		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OwnerTakesDamage);
	}
}

void UHealthComponent::OwnerTakesDamage(AActor* DamagedActor, float Damage, UDamageType const* const DamageTypeCDO, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;

	UE_LOG(LogTemp, Warning, TEXT("health is %f"), Health);

	if (Health <= 0.0f)
	{
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

void UHealthComponent::SetMaxHealth(float Value)
{
	this->MaxHealth = Value;
}

float UHealthComponent::GetHealthPercentage()
{
	return Health / MaxHealth;
}


