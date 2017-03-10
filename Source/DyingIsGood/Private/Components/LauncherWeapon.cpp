// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "../../Public/Components/LauncherWeapon.h"

void ULauncherWeapon::DoFire()
{
	//UE_LOG(LogTemp, Warning, TEXT("launcher weapon firing"));

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
		FVector TargetPoint = TargetParameters.TargetActor ? TargetParameters.TargetActor->GetActorLocation() : TargetParameters.TargetPoint;
		FVector Direction = TargetParameters.TargetPoint - SpawnPoint;
		FRotator Rotation = Direction.Rotation();
		SpawnPoint.Z += 100.0f;
		AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnPoint, Rotation);

		//fire the projectile
		if (Projectile)
		{
			Projectile->Owner = this;
			Projectile->TargetParameters = TargetParameters;
			UProjectileMovementComponent* MovementComponent = Cast<UProjectileMovementComponent>(Projectile->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
			if (MovementComponent)
			{
				AActor* Target = TargetParameters.TargetActor;
				//UE_LOG(LogTemp, Warning, TEXT("fired at %s"), *Target->GetName());
				//Seek target
				if (Target)
				{
					MovementComponent->HomingTargetComponent = Target->GetRootComponent();
				}
			}
		}
	}
}


