// cj.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//6.只想确保这个控制器能被复制,复制就是当服务器上得实体发生变化时，服务器上的变化或复制会发送给所有链接它的客户端
	//响应服务器上的更新数据发送给客户端
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;
	//每帧首先将LastActor转换为ThisActor
	LastActor = ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());
	//几种情况a.LastActor和ThisActor都是null，就是没有点击到敌人，不做任何事
	//b.LastActor是null，但是ThisActor是敌人接口，高亮ThisActor
	//c.LastActor是敌人接口，而ThisActor是null，则取消LastActor高亮
	//d.LastActor和ThisActor都不是null，也就是从一个敌人身上点击到另一个敌人身上
	//e.LastActor和ThisActor是同一个敌人 不做任何事
	if (LastActor==nullptr)
	{
		if(ThisActor!=nullptr)
		{
			//b
			ThisActor->HighLightActor();
		}
		else
		{
			//a
		}
	}
	else
	{
		if (ThisActor==nullptr)
		{
			//c
			LastActor->UnHighLightActor();
		}
		else//都有效
		{
			if (LastActor!=ThisActor)
			{
				//d
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
			else
			{
				//e
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//7，玩家控制器需要一个变量来存储输入映射上下文,去.h中声明AuraContext
	//断言，如果AuraContext无效则停止执行
	check(AuraContext);
	//9.添加输入映射文的方法是访问增强输入的本地子系统 子系统是一个单例模式，**在程序运行期间只存在一个，
	UEnhancedInputLocalPlayerSubsystem *Subsystem =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		//后面的0代表优先级，因为可以同时拥有多个输入映射上下文
		Subsystem->AddMappingContext(AuraContext,0);
	}
	//鼠标光标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	//输入方式  这样做之后就把UInputMappingContext绑定到玩家控制器上，然后还需要一个回调函数来处理实际移动角色
	FInputModeGameAndUI InputModeDate;
	InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//当窗口捕捉到光标，不隐藏光标
	InputModeDate.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeDate);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//11.使用的增强输入，将输入组件获取
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);
	//12.需要链接数据，将WASD与MoveAction链接起来 移动就会绑定到MoveAction
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//得到了FVector2D形式的输入值 可以访问它的XY
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	//想通过控制器来确定前进的方向 控制器会指向摄像机到角色的方向
	//得到了控制器的旋转
	const FRotator Rotation=GetControlRotation();
	//希望pitch（俯仰）和roll（旋转）都是0 只保留Yaw
	const FRotator YawRotation(0,Rotation.Yaw,0);
	//前向向量 FRotationMatrix类是旋转构造的旋转矩阵。通过矩阵，可以将旋转应用于向量，以便在 3D 空间中将其旋转
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn*ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);//AD
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);//WS
	}
	//一切准备号之后需要做AuraController蓝图 需要设置AuraContext MoveAction
	//然后用GameMode链接起来
}


