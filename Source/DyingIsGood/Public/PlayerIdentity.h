// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PlayerIdentity.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API UPlayerIdentity : public UObject
{
	GENERATED_BODY()
public:
	int TeamIndex;
	UPlayer* Player;
	APlayerController* Controller;
	bool IsSupportedForNetworking() const override
	{
		return true;
	}
};
