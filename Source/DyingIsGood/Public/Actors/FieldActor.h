// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerIdentity.h"
#include "FieldActor.generated.h"

UCLASS()
class DYINGISGOOD_API AFieldActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFieldActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	float Range;	

	UPROPERTY(EditInstanceOnly)
	int TeamIndex = -1;

	int GetTeamIndex() const
	{
		return TeamIndex;
	}

	UFUNCTION()
	void OwnerTakesDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
