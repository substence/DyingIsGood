// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Tower.h"
#include "../../Public/WeaponOwnerController.h"
#include "../../Public/Components/Weapon.h"

void AWeaponOwnerController::Tick(float DeltaSeconds)
{	
	AFieldActor* Tower = Cast<AFieldActor>(GetPawn());
	if (Tower)
	{
		const float Range = Tower->Range;
		const FVector TowerLocation = Tower->GetActorLocation();
		TArray<AActor*> Actors = GetTargetableActorsSortedByDistance();
		if (Actors.Num() > 0)
		{
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			NavSys->SimpleMoveToLocation(this, Actors[0]->GetActorLocation());
		}
		for (size_t i = 0; i < Actors.Num(); i++)
		{
			AActor* ActorItr = Actors[i];
			FVector ActorLocation = ActorItr->GetActorLocation();
			float DistanceToTarget = FVector::Dist(ActorLocation, TowerLocation);
			//UE_LOG(LogTemp, Warning, TEXT("range to %f"), DistanceToTarget);

			if (DistanceToTarget < Range)
			{
				//UE_LOG(LogTemp, Warning, TEXT("found potential target in range %s"), *ActorItr->GetName());

				TArray<UActorComponent*> Weapons = Tower->GetComponentsByClass(UWeapon::StaticClass());
				for (size_t j = 0; j < Weapons.Num(); j++)
				{
					//UE_LOG(LogTemp, Warning, TEXT("found potential target in range with weapon"));

					TargetingParameters Parameters;
					Parameters.TargetPoint = ActorLocation;
					Parameters.TargetActor = ActorItr;
					UWeapon* Weapon = Cast<UWeapon>(Weapons[j]);
					Weapon->Fire(Parameters);
				}
				return;
			}
		}
	}
}


TArray<AActor*> AWeaponOwnerController::GetTargetableActorsSortedByDistance()
{
	TArray<AActor*> Actors;
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (IsActorTargetable(*ActorItr))
		{
			Actors.Add(*ActorItr);
		}
	}
	/*Actors.Sort([](AActor* ip1, AActor* ip2) {
		return ip1->GetUniqueID() > ip2->GetUniqueID();//todo
	});*/
	return Actors;
}

bool AWeaponOwnerController::IsActorTargetable(AActor* Actor)
{
	return Actor->IsA(AFieldActor::StaticClass()) && Actor != this->GetPawn();
}

