// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayControllerRef = Cast<APlayerController>(GetController());

    

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (PlayControllerRef)
    {   
        FHitResult TraceHitResult;
        PlayControllerRef->GetHitResultUnderCursor
        (
            ECollisionChannel::ECC_Visibility, 
            false, 
            TraceHitResult
        );
        FVector HitLocation = TraceHitResult.ImpactPoint;
        
        RotateTurret(HitLocation);

    DrawDebugSphere
    (
        GetWorld(), 
        HitLocation, 
        20.f,
        16, 
        FColor::Red, 
        false, 
        -1.f
    );
    }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);

}


void ATank::Move(float Value)
{
    FVector DeltaLocation;
    //X = Value * DeltaTime * Speed;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    // UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaLocation.X);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation;
    //Yaw = Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::DestructionHandle()
{
    Super::DestructionHandle();
    Destroy();
}

