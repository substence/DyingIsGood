// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "../../Public/Components/LauncherWeapon.h"

void ULauncherWeapon::DoFire()
{
	Super::DoFire();
	LaunchAtDirection();
}

void ULauncherWeapon::LaunchAtDirection()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		// spawn the projectile
		World->SpawnActor<AProjectile>(ProjectileClass, GetOwner()->GetTransform());
		UE_LOG(LogTemp, Warning, TEXT("fired"));
	}
}


