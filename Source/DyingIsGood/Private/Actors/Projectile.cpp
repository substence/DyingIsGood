// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Projectile.h"
#include "Net/UnrealNetwork.h"
#include "../../Public/Components/Weapon.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	FString TestHUDString = Target ? Target->GetName() : FString(TEXT(" has no target"));
	if (Role >= ROLE_Authority)
	{
		//UE_LOG(LogTemp, Warning, TEXT("projectile spawned on server %s"), *TestHUDString);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("projectile spawned on client %s"), *TestHUDString);
	}

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));

	//todo what if there's multiple primitive components
	//UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
	if (PrimitiveComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("root component is a primitive"));
		//UE_LOG(LogTemp, Warning, TEXT("adding overlap listener"));
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollision);
	}
}

void AProjectile::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKillPending())
	{
		return;
	}
	FString TestHUDString = Target ? Target->GetName() : FString(TEXT(" has no target"));
	if (Role >= ROLE_Authority)
	{
		//UE_LOG(LogTemp, Warning, TEXT("collided on server %s"), *TestHUDString);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("collided on client %s"), *TestHUDString);
		UE_LOG(LogTemp, Warning, TEXT("collided on client with %s"), *OtherActor->GetName());
	}

	if (Target && OtherActor && Target == OtherActor)
	{
		if (Role >= ROLE_Authority)
		{
			//UE_LOG(LogTemp, Warning, TEXT("collided on server %s"), *TestHUDString);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("destroying on the client"));
		}
		Destroy();
		FDamageEvent DamageEvent;
		//UE_LOG(LogTemp, Warning, TEXT("dealing damage"));
		UGameplayStatics::ApplyDamage(Target, Damage, GetInstigatorController(), GetOwner(), UDamageType::StaticClass());

		//Target->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
		//todo : do damage to OtherActor's healthcomponent based on this projectile's damage
	}
}

AActor* AProjectile::GetIntededTarget()
{
	return Target;
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AProjectile, Target);
}

