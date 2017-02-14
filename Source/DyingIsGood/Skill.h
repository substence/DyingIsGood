// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Skill.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DYINGISGOOD_API USkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkill();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void OnRegister() override;

private:
	void OnInputPressed();

	void ActivateSkill();

	float Cost = 10.0f;

	FName InputEvent = "Skill1";

protected:
	virtual void OnActivateSkill();
};
