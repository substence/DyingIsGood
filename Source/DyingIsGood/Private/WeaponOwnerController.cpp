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
			if (FVector::DistSquaredXY(ActorLocation, TowerLocation) < Range)
			{
				TArray<UActorComponent*> Weapons = ActorItr->GetComponentsByClass(UWeapon::StaticClass());
				for (size_t i = 0; i < Weapons.Num(); i++)
				{
					TargetingParameters Parameters;
					Parameters.TargetPoint = ActorLocation;
					UWeapon* Weapon = Cast<UWeapon>(Weapons[i]);
					Weapon->Fire(Parameters);
				}
			}
		}
	}
}


