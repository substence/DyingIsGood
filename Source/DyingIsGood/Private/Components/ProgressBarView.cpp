// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "ProgressBarView.h"
#include "Engine.h"
#include "ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"


// Sets default values for this component's properties
UProgressBarView::UProgressBarView()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProgressBarView::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = this->GetOwner();

	if (Owner != NULL)
	{
		HealthComponent = Cast<UHealthComponent>(Owner->GetComponentByClass(UHealthComponent::StaticClass()));

		UWidgetComponent* Widget = Cast<UWidgetComponent>(Owner->GetComponentByClass(UWidgetComponent::StaticClass()));

		if (Widget)
		{
			//UE_LOG(LogTemp, Warning, TEXT("found the widget %s"), *Widget->GetName());
			UUserWidget* parentpoop = Widget->GetUserWidgetObject();
			if (parentpoop)
			{
				ProgressBar = Cast<UProgressBar>(parentpoop->GetWidgetFromName(FName(TEXT("ProgressBar_103"))));

				//UE_LOG(LogTemp, Warning, TEXT("found the archtype %s"), *parentpoop->GetName());
				if (ProgressBar)
				{
					//UE_LOG(LogTemp, Warning, TEXT("found the progress bar!"));
				}
			}
		}
	}
}

void UProgressBarView::OnRegister()
{
	Super::OnRegister();
}

// Called every frame
void UProgressBarView::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (ProgressBar && HealthComponent)
	{
		ProgressBar->SetPercent(HealthComponent->GetHealthPercentage());
	}
}

