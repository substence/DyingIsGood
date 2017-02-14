// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Skill.h"


// Sets default values for this component's properties
USkill::USkill(){}


// Called when the game starts
void USkill::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkill::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USkill::OnRegister()
{
	GetOwner()->GetInstigatorController()->InputComponent->BindAction(InputEvent, IE_Pressed, this, &USkill::OnInputPressed);
}

void USkill::OnInputPressed()
{
	ActivateSkill();
}

void USkill::ActivateSkill()
{
	AActor* Owner = GetOwner();
	UGameplayStatics::ApplyDamage(Owner, Cost, Owner->GetInstigatorController(), Owner, UDamageType::StaticClass());
}

void USkill::OnActivateSkill(){}

