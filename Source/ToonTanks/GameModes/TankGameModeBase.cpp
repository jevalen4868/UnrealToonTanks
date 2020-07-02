// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::ActorDied(AActor *DeadActor) {
	// Check what type of actor died. If Turret, tally, if player -> go to lose condition.
}

void ATankGameModeBase::HandleGameStart() {
	// Initialize the start countdown, turret activation, pawn check etc.
	// Call blueprint version GameStart.
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) {
	// see if the player destoryed all turrets, show win result.
	// else if turret destroyed player, show lose result.
	// Call blueprint version GameOver.
}

void ATankGameModeBase::BeginPlay() {
	// Get references and game win/lose conditions.

	// Call HandleGameStart to initialize the start countdown, turret activation, pawn check etc.
}
