// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "DyingIsGoodGameState.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API ADyingIsGoodGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;	
};
