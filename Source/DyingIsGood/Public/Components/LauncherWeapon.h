// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "../../Public/Projectile.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API ULauncherWeapon : public UWeapon
{
	GENERATED_BODY()
public:
	TSubclassOf<class AProjectile> ProjectileClass;

protected:
	virtual void DoFire() override;
	void LaunchAtDirection();	
};
