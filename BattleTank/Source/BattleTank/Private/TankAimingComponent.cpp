// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) //Since this function is public and this header file is included in Tank.h, it can get called from the constructed pointer and the OutHitLocation Out variable can get modified by raycasting in TankPlayerController
{
	UE_LOG(LogTemp, Warning, TEXT("firing at %s"), LaunchSpeed);
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


