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
	Super::OnRegister();
	UE_LOG(LogTemp, Warning, TEXT("registering"));
	AController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller)
	{
		UInputComponent* InputComponent = Controller->InputComponent;
		if (InputComponent != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("found inputcomponent"));

			InputComponent->BindAction("Skill1", IE_Pressed, this, &USkill::OnInputPressed);
		}
	}
}

void USkill::OnInputPressed()
{
	ActivateSkill();
}

void USkill::ActivateSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("activated skill"));
	AActor* Owner = GetOwner();
	UGameplayStatics::ApplyDamage(Owner, Cost, Owner->GetInstigatorController(), Owner, UDamageType::StaticClass());
}

void USkill::OnActivateSkill(){}

