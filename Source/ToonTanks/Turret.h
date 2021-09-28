// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

class ATank;
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void DestructionHandle() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;


	FTimerHandle FireRateTimerHandle;
	ATank* PlayerTank;



};
