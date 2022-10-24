// Fill out your copyright notice in the Description page of Project Settings.


#include "HeathComponent.h"
#include <Kismet/GameplayStatics.h>
#include "ToonTanksGamemode.h"

// Sets default values for this component's properties
UHeathComponent::UHeathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHeathComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHeathComponent::DamageTaken);

	ToonTanksGamemode = Cast<AToonTanksGamemode>(UGameplayStatics::GetGameMode(this));
}


void UHeathComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Health > 0.f)
	{
		Health -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Health at: %f"), Health);
	}
	if (Health <= 0.f && ToonTanksGamemode)
	{
		Health = 0.f;
		//Destroy actor
		UE_LOG(LogTemp, Warning, TEXT("Destroying actor"));
		ToonTanksGamemode->ActorDied(DamagedActor);
	}

}

// Called every frame
void UHeathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

