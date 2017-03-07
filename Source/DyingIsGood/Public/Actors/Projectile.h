// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TargetingParameters.h"
#include "Projectile.generated.h"

UCLASS()
class DYINGISGOOD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	AActor * GetIntededTarget();
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UObject* Owner;

	float Damage;

	TargetingParameters TargetParameters;
};
