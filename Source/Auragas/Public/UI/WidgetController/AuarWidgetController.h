// cj.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuarWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController*PC,APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS)
	:PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController>PlayerController=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState>PlayerState=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet>AttributeSet=nullptr;
};
/**
 * 
 */
//依赖关系是AuraUserWidget->>AuarWidgetController
//WidgetController不知道它关联了哪些控件
//但是Widget知道他们的Controller是谁
UCLASS()
class AURAGAS_API UAuarWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams&WCParams);
	//28 需要关注 AbilitySystem AttributeSet PlayerState PlayerController
	//WidgetController会访问他们

	//33 广播初始值
	virtual void  BroadcastInitailValues();
	//把回调绑定到依赖上
	virtual void BindCallBacksToDependencies();
protected:
	//28 需要关注 AbilitySystem AttributeSet PlayerState PlayerController
	//WidgetController会访问他们 这四个变量用于获取数据，让Widget显示出来
	//A 开头 → 继承自 AActor → 能放在场景里的 “实体对象”
	//U 开头 → 继承自 UObject → 引擎对象 / 资源 / 组件，不能直接放场景 必须依附于 Actor 才能存在
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;
	
};
