// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "../../Public/TargetingParameters.h"
#include "Weapon.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DYINGISGOOD_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	bool isLoaded();

	float DurationToLoaded();

	void Fire(TargetingParameters Parameters);

	void StartReload();
protected:
	virtual void DoFire();
private:
	float TimeFired = 0.0f;
};
