// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class ATank;
class ATurret;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTargetTurretCount();
	

protected:

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;
	
private:
	ATank* PlayerTank = nullptr;
	int32 TargetTurret = 0;

	APlayerControllerBase* PlayerControllerRef;

};
