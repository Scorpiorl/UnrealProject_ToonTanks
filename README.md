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
# Axis Mapping
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

# TankTurret 跟随鼠标方法
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
 
 # AddDynamic的调用要放到BeginPlay()中
应该在BeginPlay函数中添加动态委托。这样做的原因是，在Unreal中，如果你首先制作了蓝图，那么将它呈现给你的projectile cpp类，但后来添加了构造函数中声明的OnComponentHit功能，它将无法工作。 如果蓝图是从cpp类开始的，包括OnComponentHit委托，从一开始就只能在构造函数中工作。 这是一个非常常见的问题，经常被忽视。
- 两种解决方法:
- (第一种)将AddDynamic放到BeginPlay()中.
- (第二种)在完成AddDynamic相关的构造函数后,重新生成blueprint.

# 在C++ Class中新建Folder注意事项
- 由于UE4无法正确处理正在生成代码的子目录,因此在C++ Class中新建Folder后要修改Folder中.cpp的头文件,将目录删去
- 例:"GameModes/TankGameBase.h" 去掉目录改成"TankGameBase.h"即可正常编译