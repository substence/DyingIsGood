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
}

bool UWeapon::isLoaded()
{
	return DurationToLoaded() <= 0;
}

float UWeapon::DurationToLoaded()
{
	return GetWorld()->TimeSeconds - TimeFired;
}

void UWeapon::Fire(TargetingParameters Parameters)
{
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
	TimeFired = GetWorld()->TimeSeconds;
}

