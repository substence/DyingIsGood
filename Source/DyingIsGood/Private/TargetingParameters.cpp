// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Net/UnrealNetwork.h"
#include "TargetingParameters.h"

UTargetingParameters::UTargetingParameters()
{
	//bReplicates = true;
}

void UTargetingParameters::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTargetingParameters, TargetPoint);
	DOREPLIFETIME(UTargetingParameters, TargetActor);
}


