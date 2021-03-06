// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "ImmolationSkill.h"
#include "Minion.h"

UImmolationSkill::UImmolationSkill()
{
	PrimaryComponentTick.bCanEverTick = true;
	Damage = 1.0f;
}

void UImmolationSkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("ticking immolation"));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("immolation active"));

		AActor* Owner = GetOwner();
		if (Owner->IsA<ACharacter>())
		{
			UE_LOG(LogTemp, Warning, TEXT("immolation has owner"));

			//UGameplayStatics::ApplyDamage(Owner, Damage, Owner->GetInstigatorController(), Owner, UDamageType::StaticClass());
			ACharacter* Character = Cast<ACharacter>(Owner);
			TArray<AActor*> Touching;
			Character->GetCapsuleComponent()->GetOverlappingActors(Touching);
			for (size_t i = 0; i < Touching.Num(); i++)
			{
				AActor* Actor = Touching[i];
				if (!Actor->IsA(AMinion::StaticClass()))
				{
					UGameplayStatics::ApplyDamage(Actor, Damage, Character->GetInstigatorController(), Character, UDamageType::StaticClass());
				}
			}
		}

	}
}
