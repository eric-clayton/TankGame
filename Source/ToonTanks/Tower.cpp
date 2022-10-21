// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TargetTank();

}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//Intialize Tank actor
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::TargetTank()
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
			// If in range, rotate turret towards Tank
			RotateTurret(TankLocation);
		}
	}
}
