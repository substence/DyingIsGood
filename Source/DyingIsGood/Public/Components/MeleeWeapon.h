// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class DYINGISGOOD_API UMeleeWeapon : public UWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage;
protected:
	virtual void DoFire() override;	
};
