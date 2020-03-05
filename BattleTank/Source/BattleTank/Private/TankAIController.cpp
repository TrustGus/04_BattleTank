// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto TankAIController = GetTankAIControlledTank();

	auto PlayerPawn = GetPlayerTank();

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s unable to find player controlled tank"), *(TankAIController->GetName()));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController (%s) found player (%s)"), *(TankAIController->GetName()), *(PlayerPawn->GetName()));
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


ATank* ATankAIController::GetTankAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


