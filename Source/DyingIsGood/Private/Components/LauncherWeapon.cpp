// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "../../Public/Components/LauncherWeapon.h"

void ULauncherWeapon::DoFire()
{
	UE_LOG(LogTemp, Warning, TEXT("launcher weapon firing"));

	Super::DoFire();
	LaunchAtDirection();
}

void ULauncherWeapon::LaunchAtDirection()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		// spawn the projectile
		FTransform SpawnTransform = GetOwner()->GetTransform();
		FVector SpawnPoint = SpawnTransform.GetLocation();
		SpawnPoint.Z += 100.0f;
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnPoint, GetOwner()->GetActorRotation());

		//fire the projectile
		if (Projectile)
		{
			UMovementComponent* MovementComponent = Cast<UMovementComponent>(Projectile->GetComponentByClass(UMovementComponent::StaticClass()));
			if (MovementComponent)
			{
				UE_LOG(LogTemp, Warning, TEXT("fired"));
				FVector Direction = SpawnPoint - Parameters.TargetPoint;
				Direction.Normalize();
				MovementComponent->Velocity = Direction;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("fired"));
	}
}


