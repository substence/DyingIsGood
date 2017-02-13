// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DyingIsGoodAIController.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API ADyingIsGoodAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADyingIsGoodAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	void SpawnMinion(FTransform Start, FVector End);
	AActor* FindFirstTriggerWithTag(FName Name);
	class UClass* MinionClass;
	FTransform SpawnPoint;
	FTransform TargetPoint;
	float TimeOfLastDeploy;
	float DeployDelay = 15.0f;
};