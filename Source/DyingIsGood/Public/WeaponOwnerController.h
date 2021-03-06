// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "WeaponOwnerController.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API AWeaponOwnerController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;	
	TArray<AFieldActor*> GetTargetableActorsSortedByDistance(AFieldActor* PossessdPawn);
	bool IsActorTargetable(AFieldActor* PossessdPawn, AFieldActor* Actor);
	virtual void BeginPlay() override;
};
