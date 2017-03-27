// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "TargetingParameters.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API UTargetingParameters : public UObject
{
	GENERATED_BODY()
public:
	UTargetingParameters();
	UPROPERTY(Replicated)
	FVector TargetPoint;
	UPROPERTY(Replicated)
	AActor* TargetActor;
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
};
