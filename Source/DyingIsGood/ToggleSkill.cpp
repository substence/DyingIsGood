// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "ToggleSkill.h"

void UToggleSkill::OnActivateSkill()
{
	Super::OnActivateSkill();
	IsActive = !IsActive;
;}
