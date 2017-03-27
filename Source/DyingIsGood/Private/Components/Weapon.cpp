#include "DyingIsGood.h"
#include "Net/UnrealNetwork.h"
#include "../../Public/Components/Weapon.h"

UWeapon::UWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();	
	SetIsReplicated(true);
}

void UWeapon::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	//UE_LOG(LogTemp, Warning, TEXT("UWeapon::DurationToLoaded load duration %f"), LoadDuration);

	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!bIsLoaded && DurationToLoaded() <= 0)
	{
		bIsLoaded = true;
	}
}

float UWeapon::DurationToLoaded()
{
	//UE_LOG(LogTemp, Warning, TEXT("UWeapon::DurationToLoaded load duration %f"), LoadDuration);
	//UE_LOG(LogTemp, Warning, TEXT("UWeapon::DurationToLoaded duration since last fire %f"), GetWorld()->TimeSeconds - TimeFired);

	return LoadDuration - (GetWorld()->TimeSeconds - TimeFired);
}

void UWeapon::Fire(UTargetingParameters* Parameters)
{
	//UE_LOG(LogTemp, Warning, TEXT("attempting fire"));
	Target = Parameters->TargetActor;
	if (!IsLoaded())
	{
		return;
	}
	DoFire();
	StartReload();
}

void UWeapon::DoFire()
{

}

void UWeapon::StartReload()
{
	bIsLoaded = false;
	TimeFired = GetWorld()->TimeSeconds;
}

void UWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	//DOREPLIFETIME(UWeapon, TargetParameters);
	DOREPLIFETIME(UWeapon, Target);
}

