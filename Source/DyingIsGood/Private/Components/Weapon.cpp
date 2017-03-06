#include "DyingIsGood.h"
#include "../../Public/Components/Weapon.h"
//#include "../../Public/TargetingParameters.h"

UWeapon::UWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();	
}

void UWeapon::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!bIsLoaded && DurationToLoaded() <= 0)
	{
		bIsLoaded = true;
	}
}

float UWeapon::DurationToLoaded()
{
	return LoadDuration - (GetWorld()->TimeSeconds - TimeFired);
}

void UWeapon::Fire(TargetingParameters Parameters)
{
	//UE_LOG(LogTemp, Warning, TEXT("attempting fire"));
	this->Parameters = Parameters;
	if (!isLoaded())
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

