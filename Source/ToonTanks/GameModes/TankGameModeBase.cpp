// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Tank.h"
#include "ToonTanks/Turret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnableState(false);
        }
        
    }
    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if (--TargetTurret == 0)
        {
            HandleGameOver(true);
        }
    }
    
    
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TArray<AActor *> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}

//为了能在蓝图中直接使用GameStart()/GameOver()因此需要设置HandleGameStart()/HandleGameOver()以便在C++中完善功能.
void ATankGameModeBase::HandleGameStart()
{   
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TargetTurret = GetTargetTurretCount();
    
    GameStart();
    if (PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnableState(false);

        
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    GameOver(PlayerWon);
}
