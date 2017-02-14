// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skill.h"
#include "ToggleSkill.generated.h"

/**
 * 
 */
UCLASS()
class DYINGISGOOD_API UToggleSkill : public USkill
{
	GENERATED_BODY()
public:
	bool IsActive;

	virtual void OnActivateSkill() override;
};
