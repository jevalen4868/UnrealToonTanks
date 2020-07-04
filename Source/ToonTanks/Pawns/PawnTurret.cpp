// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay() {
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) {
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() {
	// If Player == null || is dead THEN BAIL!
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive()) {
		return;
	}
	// If Player IS in range THEN FIRE!
	if (ReturnDistanceToPlayer() <= FireRange) {
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer() {
	// Check if we have a valid ref to player.
	if (!PlayerPawn) {
		return 0.0f;
	}
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	return Distance;
}

void APawnTurret::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}
