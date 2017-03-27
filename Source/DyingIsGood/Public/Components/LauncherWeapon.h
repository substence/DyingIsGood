// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "../Actors/Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "../TargetingParameters.h"
#include "Public/TargetingParameters.h"
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

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void DoFire() override;

	//UFUNCTION(Reliable, Server, WithValidation)
	//void LaunchAtDirection(UWorld* World, TSubclassOf<class AProjectile> Type, FVector SpawnPoint, FRotator Rotation);

	void LaunchAtDirection_Implementation(UWorld* World, TSubclassOf<class AProjectile> Type, FVector SpawnPoint, FRotator Rotation);

	bool LaunchAtDirection_Validate(UWorld* World, TSubclassOf<class AProjectile> Type, FVector SpawnPoint, FRotator Rotation);
};
