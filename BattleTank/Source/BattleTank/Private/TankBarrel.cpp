// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	//Movet the barrel right ammount

	//give a max elevation speed, and the frame time

	float RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0)); //Sets rotation

	return;
}