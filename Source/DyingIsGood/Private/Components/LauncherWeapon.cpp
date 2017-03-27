// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Public/TargetingParameters.h"
#include "Public/Actors/FieldActor.h"
#include "../../Public/Components/LauncherWeapon.h"

void ULauncherWeapon::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("creating launcherweapon %d"), this->GetUniqueID());
}

void ULauncherWeapon::DoFire()
{
	if (this->GetOwnerRole() >= ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT(" ULauncherWeapon::DoFire with auth"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" ULauncherWeapon::DoFire without auth"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("launcher weapon firing"));
	//UE_LOG(LogTemp, Warning, TEXT("firing launcherweapon %d"), this->GetUniqueID());

	Super::DoFire();
	UWorld* const World = GetWorld();
	AActor* Owner = GetOwner();
	if (World != NULL && Owner != NULL)
	{
		// spawn the projectile
		FTransform SpawnTransform = Owner->GetTransform();
		FVector SpawnPoint = SpawnTransform.GetLocation();
		//FVector TargetPoint = TargetParameters->TargetActor ? TargetParameters->TargetActor->GetActorLocation() : TargetParameters->TargetPoint;
		FVector Direction = Target->GetActorLocation() - SpawnPoint;
		FRotator Rotation = Direction.Rotation();
		SpawnPoint.Z += 100.0f;
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = Owner;
		LaunchAtDirection_Implementation(World, ProjectileClass, SpawnPoint, Rotation);
		AFieldActor* FieldActor = Cast<AFieldActor>(GetOwner());
	}
}

void ULauncherWeapon::LaunchAtDirection_Implementation(UWorld* World, TSubclassOf<class AProjectile> Type, FVector SpawnPoint, FRotator Rotation)
{
	AProjectile* Projectile = World->SpawnActor<AProjectile>(Type, SpawnPoint, Rotation);

	//fire the projectile
	if (Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawned projectile"));

		Projectile->Target = Target;
		FString TestHUDString = Target ? Target->GetName() : FString(TEXT(" has no target"));

		UE_LOG(LogTemp, Warning, TEXT("set projectile target parameters to %s"), *TestHUDString);

		UProjectileMovementComponent* MovementComponent = Cast<UProjectileMovementComponent>(Projectile->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
		if (MovementComponent)
		{
			//Seek target
			if (Target)
			{
				MovementComponent->HomingTargetComponent = Target->GetRootComponent();
			}
		}
	}
}

bool ULauncherWeapon::LaunchAtDirection_Validate(UWorld* World, TSubclassOf<class AProjectile> Type, FVector SpawnPoint, FRotator Rotation)
{
	return true;
}

void ULauncherWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString TestHUDString = Target ? *Target->GetName() : FString(TEXT(" false"));
	if (GetOwnerRole() >= ROLE_Authority)
	{
		//UE_LOG(LogTemp, Warning, TEXT("collided on server %s"), *TestHUDString);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("collided on client %s"), *TestHUDString);
	}
}


