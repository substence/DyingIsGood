// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "DyingIsGoodGameState.h"

void ADyingIsGoodGameState::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("dticking gamestate"));
	Super::Tick(DeltaTime);
}


