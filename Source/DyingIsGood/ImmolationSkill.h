// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ToggleSkill.h"
#include "ImmolationSkill.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API UImmolationSkill : public UToggleSkill
{
	GENERATED_BODY()
public:
	UImmolationSkill();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float Damage;	
};
