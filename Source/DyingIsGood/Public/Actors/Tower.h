// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FieldActor.h"
#include "Tower.generated.h"

UCLASS()
class DYINGISGOOD_API ATower : public AFieldActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
