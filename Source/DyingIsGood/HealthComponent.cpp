// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::OnRegister()
{
	Super::OnRegister();
	
	if (Max)
	{
		SetMaxHealth(Max);
		SetHealth(Max);
	}

	AActor* Owner = this->GetOwner();

	if (Owner != NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("adding take damage listener"));

		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OwnerTakesDamage);
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::OwnerTakesDamage(AActor* DamagedActor, float Damage, UDamageType const* const DamageTypeCDO, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;

	//UE_LOG(LogTemp, Warning, TEXT("owner took damage, health is %f"), Health);

	if (Health <= 0.0f)
	{
		GetOwner()->Destroy();
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


