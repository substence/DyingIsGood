// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DyingIsGood.h"
#include "Net/UnrealNetwork.h"
#include "Public/PlayerIdentity.h"
#include "DyingIsGoodPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "DyingIsGoodCharacter.h"
#include "DyingIsGoodAIController.h"

ADyingIsGoodPlayerController::ADyingIsGoodPlayerController()
{
	bShowMouseCursor = true;
	bReplicates = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADyingIsGoodPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("player beginplay %d"), TeamIndex);
}

void ADyingIsGoodPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ADyingIsGoodPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADyingIsGoodPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADyingIsGoodPlayerController::StartSpawnFieldActorAtMouse);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADyingIsGoodPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADyingIsGoodPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ADyingIsGoodPlayerController::OnResetVR);
}

void ADyingIsGoodPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADyingIsGoodPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ADyingIsGoodCharacter* MyPawn = Cast<ADyingIsGoodCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ADyingIsGoodPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ADyingIsGoodPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADyingIsGoodPlayerController::StartSpawnFieldActorAtMouse()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnFieldActorAtMouse_Implementation"));

	if (FieldActorToSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));

		FHitResult result;
		GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, result);
		if (!result.ImpactPoint.IsZero())
		{
			UE_LOG(LogTemp, Warning, TEXT("2"));
			//ImpactPoint = result.ImpactPoint;
			SpawnFieldActorAtMouse(result.ImpactPoint);
		}
	}
}

void ADyingIsGoodPlayerController::SpawnFieldActorAtMouse_Implementation(FVector_NetQuantize ImpactPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("3"));

	FActorSpawnParameters SpawnParameters;
	AFieldActor* Projectile = GetWorld()->SpawnActor<AFieldActor>(FieldActorToSpawn, ImpactPoint, FRotator::ZeroRotator);
	if (Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("4"));

		Projectile->TeamIndex = TeamIndex;
		Projectile->SetOwner(this);
	}
}

bool ADyingIsGoodPlayerController::SpawnFieldActorAtMouse_Validate(FVector_NetQuantize ImpactPoint)
{
	return true;
}

void ADyingIsGoodPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADyingIsGoodPlayerController, TeamIndex);
}
