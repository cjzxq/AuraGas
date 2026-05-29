// cj.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
UCLASS()
class AURAGAS_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();//5.构造函数
	//16.每帧追踪高亮
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;//10.

	
private:
	//8.还有前向声明,需要在用到AuraContext的时候包含有UInputMappingContext，只有在访问模块权限的时候才能成功包含这个头文件
	//包含Enhance Input类的头文件的Enhance Input模块 需要去Aura.Build.cs中将Enhance Input添加到MoudleNames中
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere, Category = "Input")//11.
	TObjectPtr<UInputAction>MoveAction;
	//12.需要绑定一个函数，响应输入来移动我们的角色 所以需要一个移动角色的函数
	void Move(const FInputActionValue& InputActionValue);
	//17.要在光标下获取命中结果
	void CursorTrace();
	IEnemyInterface *LastActor;
	IEnemyInterface *ThisActor;
};
