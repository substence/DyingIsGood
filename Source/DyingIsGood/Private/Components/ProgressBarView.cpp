// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "ProgressBarView.h"
#include "Engine.h"
#include "ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Actors/FieldActor.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"

UProgressBarView::UProgressBarView()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProgressBarView::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = this->GetOwner();

	if (Owner != NULL)
	{
		HealthComponent = Cast<UHealthComponent>(Owner->GetComponentByClass(UHealthComponent::StaticClass()));

		ProgressBarWidget = CreateWidget<UUserWidget>(GetWorld(), ProgressBarClass);
		if (ProgressBarWidget)
		{
			//UE_LOG(LogTemp, Warning, TEXT("created progressbar widget"));
			ProgressBarWidget->AddToViewport();
			ProgressBar = Cast<UProgressBar>(ProgressBarWidget->GetWidgetFromName(FName(TEXT("ProgressBar_103"))));
		}

		/*UWidgetComponent* Widget = Cast<UWidgetComponent>(Owner->GetComponentByClass(UWidgetComponent::StaticClass()));

		if (Widget)
		{
			//UE_LOG(LogTemp, Warning, TEXT("found the widget %s"), *Widget->GetName());
			UUserWidget* parentpoop = Widget->GetUserWidgetObject();
			if (parentpoop)
			{
				ProgressBar = Cast<UProgressBar>(parentpoop->GetWidgetFromName(FName(TEXT("ProgressBar_103"))));

				/*UE_LOG(LogTemp, Warning, TEXT("found the archtype %s"), *parentpoop->GetName());
				if (ProgressBar)
				{
					UE_LOG(LogTemp, Warning, TEXT("found the progress bar!"));
				}
			}
		}*/
	}
}

void UProgressBarView::OnRegister()
{
	Super::OnRegister();
}

void UProgressBarView::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (ProgressBarWidget)
	{
		ProgressBarWidget->RemoveFromViewport();
	}
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

// Called every frame
void UProgressBarView::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (ProgressBar && HealthComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("1"));

		ProgressBar->SetPercent(HealthComponent->GetHealthPercentage());
		AFieldActor* Owner = Cast<AFieldActor>(GetOwner());
		if (Owner)
		{
			//UE_LOG(LogTemp, Warning, TEXT("2"));


			//APlayerController* Controller = Cast<APlayerController>(Owner->GetInstigatorController());
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			if (Controller)
			{
				//UE_LOG(LogTemp, Warning, TEXT("3"));

				FVector2D ScreenPosition;
				bool bIsActorOnScreen = Controller->ProjectWorldLocationToScreen(Owner->GetActorLocation(), ScreenPosition);
				if (ProgressBarWidget)
				{
					//UE_LOG(LogTemp, Warning, TEXT("4"));

					ProgressBarWidget->Visibility = bIsActorOnScreen ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
					if (bIsActorOnScreen)
					{
						//UE_LOG(LogTemp, Warning, TEXT("5"));

						ProgressBarWidget->SetPositionInViewport(ScreenPosition);
					}
				}
			}
		}
		//this->GetOwner()->GetInstigatorController()->
	}
}

