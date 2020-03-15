// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	auto RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}