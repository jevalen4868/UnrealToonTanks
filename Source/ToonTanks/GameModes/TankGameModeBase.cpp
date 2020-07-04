// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerController/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::ActorDied(AActor *DeadActor) {
	if (DeadActor == PlayerTank) {
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);
		if (PlayerControllerRef) {
			PlayerControllerRef->SetPlayerEnabled(false);
		}
	}
	else if (APawnTurret *DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
		DestroyedTurret->PawnDestroyed();
		TargetTurrets--;
		if (TargetTurrets == 0) {
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart() {	
	GameStart();
	if (PlayerControllerRef) {
		PlayerControllerRef->SetPlayerEnabled(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabled, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) {	
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() {
	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();
	TArray<AActor *> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
	return TurretActors.Num();
}

void ATankGameModeBase::BeginPlay() {
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	HandleGameStart();
	Super::BeginPlay();
}
