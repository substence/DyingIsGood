// Fill out your copyright notice in the Description page of Project Settings.

#include "DyingIsGood.h"
#include "Projectile.h"
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
	
	UE_LOG(LogTemp, Warning, TEXT("adding projectile"));

	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));

	//todo what if there's multiple primitive components
	//UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
	if (PrimitiveComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("root component is a primitive"));
		UE_LOG(LogTemp, Warning, TEXT("adding overlap listener"));
		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollision);
	}
}

void AProjectile::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* Target = GetIntededTarget();
	if (Target && OtherActor && Target == OtherActor)
	{
		Destroy();
		FDamageEvent DamageEvent;
		UE_LOG(LogTemp, Warning, TEXT("dealing damage"));
		Target->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);
		//todo : do damage to OtherActor's healthcomponent based on this projectile's damage
	}
}

AActor* AProjectile::GetIntededTarget()
{
	return TargetParameters.TargetActor;
	/*AActor* Target;
	if (Owner && Owner->IsA(UWeapon::StaticClass()))
	{
		UWeapon* Weapon = Cast<UWeapon>(Owner);
		if (Weapon)
		{
			Target = Weapon->GetTargetingParameters().TargetActor;
			return Target;
		}
	}
	return NULL;*/
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

