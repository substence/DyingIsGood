// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ProgressBar.h"
#include "HealthComponent.h"
#include "ProgressBarView.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DYINGISGOOD_API UProgressBarView : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProgressBarView();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void OnRegister() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ProgressBarClass;

	UPROPERTY(EditDefaultsOnly)
	UProgressBar* ProgressBar;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
private:
	UUserWidget* ProgressBarWidget;

	UHealthComponent* HealthComponent;
};
