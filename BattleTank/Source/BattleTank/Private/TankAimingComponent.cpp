// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bHaveAimSolution)
	{
		auto TankName = GetOwner()->GetName();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"),*TankName,*AimDirection.ToString());
	};


}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Get current barrel rotation and aim direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation; //difference to move
	
	//MoveBarrel(FVector AimDirection)
			//Get current location of barrel
			//Get desired locatio, i.e. aim direction
			//path between two locations, set yaw, pitch and roll where movement should occur. really itll just be in two directions
			//broadcast values to bp to be used to set movement
}

