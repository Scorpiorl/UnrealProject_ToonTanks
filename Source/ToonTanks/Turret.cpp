// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATurret::ATurret()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerTank || ReturnDistanceToPlayer() > FireRange )
    {
        return;
    }

    RotateTurret(PlayerTank->GetActorLocation());
}

void ATurret::CheckFireCondition()
{
    //If Player == null || is Dead THEN BAIL!!
    if (!PlayerTank)
    {
        return;
    }
    //If Player is in  range THEN FIRE!!
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        //Fire
        Fire();
    }
    

}

float ATurret::ReturnDistanceToPlayer()
{
    if (!PlayerTank)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}