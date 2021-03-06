// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "ToonTanks/ProjectileBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Colider"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpwanPiont = CreateDefaultSubobject<USceneComponent>(TEXT("Spwan Point"));
	ProjectileSpwanPiont->SetupAttachment(TurretMesh);
	//当初是以ActorComponent类型来创建HealthComponent的,因此此处不需要在附着
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector TargetLocation = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation =FVector(TargetLocation - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void ABasePawn::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpwanPiont->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpwanPiont->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}


void ABasePawn::HandleDestruction()
{
	// --- Universal functionality --- 
	// Play death effects particle, sound and camera shake. 
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExploseCameraShake);
	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self. 

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.
}



