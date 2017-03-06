// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Tower.h"
#include "../../Public/WeaponOwnerController.h"
#include "../../Public/Components/Weapon.h"

void AWeaponOwnerController::Tick(float DeltaSeconds)
{	
	ATower* Tower = Cast<ATower>(GetPawn());
	if (Tower)
	{
		const float Range = Tower->Range;
		const FVector TowerLocation = Tower->GetActorLocation();
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			FVector ActorLocation = ActorItr->GetActorLocation();
			if (ActorLocation == TowerLocation)
			{
				continue;
			}

			if (!ActorItr->IsA(ACharacter::StaticClass()))
			{
				continue;
			}
			float DistanceToTarget = FVector::Dist(ActorLocation, TowerLocation);
			//UE_LOG(LogTemp, Warning, TEXT("range to %f"), DistanceToTarget);

			if (DistanceToTarget < Range)
			{
				//UE_LOG(LogTemp, Warning, TEXT("found potential target in range %s"), *ActorItr->GetName());

				TArray<UActorComponent*> Weapons = Tower->GetComponentsByClass(UWeapon::StaticClass());
				for (size_t i = 0; i < Weapons.Num(); i++)
				{
					//UE_LOG(LogTemp, Warning, TEXT("found potential target in range with weapon"));

					TargetingParameters Parameters;
					Parameters.TargetPoint = ActorLocation;
					Parameters.TargetActor = *ActorItr;
					UWeapon* Weapon = Cast<UWeapon>(Weapons[i]);
					Weapon->Fire(Parameters);
				}
				return;
			}
		}
	}
}


