# ToonTanks
Developed with Unreal Engine 4

# C++中.,->,::使用方法

|Left Term|Accessor|Example|
|-|-|-|
|Instance or Reference|.|myGrab.Grab() <br> MyBullCowCount.Bull()|
|Pointer|->|MyGrabPtr->Grab() <br> MyGrabPtr->Reach|
|Class, Enum, Namespace|::|UGrabber::Grab <br> std::cout|

# Component
- USceneComponent
  - Has a transform
  - Support attachment
  - No visible representation
- UCapsuleComponent
  - Handle Collision
- UStaticMeshComponent
  - Visible representation
  
# Action Mapping & Axis Mapping

## Action Mapping
```C++
void UInput::BeginPlay()
{
	Super::BeginPlay();
  //获取输入组件
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  //绑定事件
	if(InputComponent){
		InputComponent->BindAction("Kiss", IE_Pressed, this, &UInput::InputEvent);
	}
}

void UInput::InputEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Kiss lovely bunny!"))
}
```
## Axis Mapping
```C++
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
}

void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
}
```

**GetWorldDeltaSeconds & GetWorldTimeManager**

1. **GetWorldDeltaSeconds** : Returns the frame delta time in seconds, adjusted by time dilation.
2. **GetWorldTimeManager** : Returns TimerManager instance for this world.

## TankTurret 跟随鼠标方法
```C++
void ATank::BeginPlay()
{
	Super::BeginPlay();
    //Tank.h 中 APlayerController* PlayControllerRef;
    PlayControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (PlayControllerRef)
    {   
        FHitResult TraceHitResult;
        PlayControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;
        
        RotateTurret(HitLocation);
    }
}
```
 