// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *ParticleTrail;
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem *HitParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShake> HitShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed{ 1300.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage{ 50.0f };
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase *HitSound;
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase *LaunchSound;
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
