// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TargetTank();
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//Intialize Tank actor
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

}

void ATower::CheckFireCondition()
{
	if (IsTankInRange() && Tank->bAlive)
	{
		Fire();
	}
}
bool ATower::IsTankInRange()
{
	// Check For valid Tank actor
	if (Tank)
	{
		//Find Distance to the Tank
		FVector TankLocation = Tank->GetActorLocation();
		float Distance = FVector::Dist(GetActorLocation(), TankLocation);
		// Check to see if Tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
bool ATower::IsTankInRange(FVector& OutTankLocation)
{
	// Check For valid Tank actor
	if (Tank)
	{
		//Find Distance to the Tank
		OutTankLocation = Tank->GetActorLocation();
		float Distance = FVector::Dist(GetActorLocation(), OutTankLocation);
		// Check to see if Tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void ATower::TargetTank()
{
	FVector TankLocation;
	if (IsTankInRange(TankLocation))
	{
		RotateTurret(TankLocation);
	}
}
