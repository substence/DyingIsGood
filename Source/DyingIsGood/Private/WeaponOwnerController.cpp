// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Tower.h"
#include "../../Public/WeaponOwnerController.h"
#include "../../Public/Components/Weapon.h"
#include "Minion.h"

void AWeaponOwnerController::Tick(float DeltaSeconds)
{	
	//UE_LOG(LogTemp, Warning, TEXT("issuing move command on %s"), *GetPawn()->GetName());

	AFieldActor* Tower = Cast<AFieldActor>(GetPawn());

	if (Tower)
	{
		const float Range = Tower->Range;
		const FVector TowerLocation = Tower->GetActorLocation();
		TArray<AFieldActor*> Actors = GetTargetableActorsSortedByDistance(Tower);
		if (Actors.Num() > 0)
		{
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			NavSys->SimpleMoveToLocation(this, Actors[Actors.Num() - 1]->GetActorLocation());
			//UE_LOG(LogTemp, Warning, TEXT("issuing move command on %s"), *Tower->GetName());
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


TArray<AFieldActor*> AWeaponOwnerController::GetTargetableActorsSortedByDistance(AFieldActor* PossessdPawn)
{
	TArray<AFieldActor*> Actors;
	FVector PawnLocation = PossessdPawn->GetActorLocation();
	for (TActorIterator<AFieldActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (IsActorTargetable(PossessdPawn, *ActorItr))
		{
			Actors.Add(*ActorItr);
		}
	}
	Actors.Sort([PawnLocation](AFieldActor& ip1, AFieldActor& ip2)
	{
		return FVector::Dist(ip1.GetActorLocation(), PawnLocation) > FVector::Dist(ip2.GetActorLocation(), PawnLocation);
	});
	return Actors;
}

bool AWeaponOwnerController::IsActorTargetable(AFieldActor* PossessdPawn, AFieldActor* Actor)
{

	if (PossessdPawn->IsA(AMinion::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("CHECKING IF ACTOR IS TARGETABLE, THIS IS %d"), PossessdPawn->GetTeamIndex());
		UE_LOG(LogTemp, Warning, TEXT("CHECKING IF ACTOR IS TARGETABLE, TARGET IS %d"), Actor->GetTeamIndex());
	}

	return Actor->IsA(AFieldActor::StaticClass()) && Actor != PossessdPawn && PossessdPawn->GetTeamIndex() != Actor->GetTeamIndex();
}

