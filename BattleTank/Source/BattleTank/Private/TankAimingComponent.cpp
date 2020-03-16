// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) //Since this function is public and this header file is included in Tank.h, it can get called from the constructed pointer and the OutHitLocation Out variable can get modified by raycasting in TankPlayerController
{	
	if (!Barrel) { return; }

	FVector OutLaunchVelocity; //OUT
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		0,
		0,
		false,
		ESuggestProjVelocityTraceOption::DoNotTrace //parameter must be presented to avoid bug
		);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation(); //Get current barrel rotation and aim direction
	auto AimAsRotator = AimDirection.Rotation(); //get desired direction
	auto DeltaRotator = AimAsRotator - BarrelRotation; //difference to move

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!Turret) { return; } //pointer protection

	auto TurretRotation = Turret->GetForwardVector().Rotation(); //Get current barrel rotation and aim direction
	auto AimAsRotator = AimDirection.Rotation(); //get desired direction
	auto DeltaRotator = AimAsRotator - TurretRotation; //difference to move

	Turret->RotateTurret(DeltaRotator.Yaw);
}

