// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::PawnDestroyed() {
	HandleDestruction();
}

void APawnBase::RotateTurret(FVector LookAtTarget) {
	// update turretmesh rotation to face towards the LookAtTarget passed in from the child class.
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector( LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z ));
	// Rotate turret.
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() {	
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location towards Rotation.
	if (ProjectileClass) {
		FVector SpawnLocation{ ProjectileSpawnPoint->GetComponentLocation() };
		FRotator SpawnRotation{ ProjectileSpawnPoint->GetComponentRotation() };
		AProjectileBase *TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,
			SpawnLocation,
			SpawnRotation);
		TempProjectile->SetOwner(this);			
	}
}

void APawnBase::HandleDestruction() {
	// universal functionality 
	// Play death effects particle, sound and camera shake.

	// The do unique child overrides.
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self.

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement Input.
}
