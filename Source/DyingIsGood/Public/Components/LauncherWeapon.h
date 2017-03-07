// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "../Actors/Projectile.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DYINGISGOOD_API ULauncherWeapon : public UWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AProjectile> ProjectileClass;

protected:
	virtual void DoFire() override;
	void LaunchAtDirection();	
};
