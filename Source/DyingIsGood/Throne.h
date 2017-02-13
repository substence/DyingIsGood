// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HealthComponent.h"
#include "Runtime/Engine/Classes/Engine/TriggerBox.h"
#include "Throne.generated.h"

UCLASS()
class DYINGISGOOD_API AThrone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrone();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
private:
	UHealthComponent* Health;	
};
