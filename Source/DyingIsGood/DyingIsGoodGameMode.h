// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "DyingIsGoodGameMode.generated.h"

UCLASS(minimalapi)
class ADyingIsGoodGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADyingIsGoodGameMode();
	virtual void InitGameState() override;
};



