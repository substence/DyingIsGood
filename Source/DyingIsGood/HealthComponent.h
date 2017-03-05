// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DYINGISGOOD_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	float GetHealth();
	void SetHealth(float Value);
	void SetMaxHealth(float Value);

	float GetHealthPercentage();

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float Max;

private:
	float Health = 100.0f;
	float MaxHealth = 100.0f;
	UFUNCTION()
	void OwnerTakesDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};