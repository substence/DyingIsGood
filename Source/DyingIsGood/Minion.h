// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FieldActor.h"
#include "HealthComponent.h"
#include "Minion.generated.h"

UCLASS()
class DYINGISGOOD_API AMinion : public AFieldActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void DamageAllNearbyActors();

	void DamageActor(AActor * Actor);

	UHealthComponent* Health;
};
