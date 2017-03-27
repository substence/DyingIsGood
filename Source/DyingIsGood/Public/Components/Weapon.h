// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "../TargetingParameters.h"
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

	bool IsLoaded() const { return bIsLoaded; };

	//UTargetingParameters* GetTargetingParameters() const { return TargetParameters; };

	float DurationToLoaded();

	void Fire(UTargetingParameters* Parameters);

	void StartReload();

	UPROPERTY(Replicated)
	AActor* Target;

	/*UPROPERTY(Replicated)
	UTargetingParameters* TargetParameters;*/

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float LoadDuration = 15.0f;

protected:
	virtual void DoFire();


private:
	float TimeFired = 0.0f;
	bool bIsLoaded = true;
};
