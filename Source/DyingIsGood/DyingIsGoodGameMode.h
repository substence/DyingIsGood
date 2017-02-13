// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "DyingIsGoodGameMode.generated.h"

UCLASS()
class ADyingIsGoodGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADyingIsGoodGameMode();
	virtual void InitGameState() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	class UClass* MinionClass;
private:
	float TimeOfLastDeploy;
	float DeployDelay = 1.0f;
	FTransform SpawnPoint;
	FTransform TargetPoint;
	void SpawnMinion(FTransform Start, FVector End);
	AActor* FindFirstTriggerWithTag(FName Name);
};



