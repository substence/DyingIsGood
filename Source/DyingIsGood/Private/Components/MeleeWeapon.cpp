// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "MeleeWeapon.h"

void UMeleeWeapon::DoFire()
{
	AActor* Target = TargetParameters.TargetActor;
	AActor* Owner = GetOwner();
	//UE_LOG(LogTemp, Warning, TEXT("melee attemping fire"));

	if (Target && Owner)
	{
		//UE_LOG(LogTemp, Warning, TEXT("melee firing"));

		UGameplayStatics::ApplyDamage(Target, Damage, Owner->GetInstigatorController(), Owner, UDamageType::StaticClass());
	}
}



