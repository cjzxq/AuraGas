// cj.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	//30
	if (OverlayWidgetController == nullptr)
	{
		//如果是(this,OverlayWidgetClass)就会出错,应该是OverlayWidgetControllerClass
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//31 创建WidgetController，Widget，并把控件添加到桌面上
	//创建并将小部件添加到视口（ViewPort）   什么时候调用InitOverlay函数呢？
	//在什么时候才能确定所有变量都初始化好了呢？ 要兼顾客户端服务端两种情况 
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass 没有选择值，请在AAuraHUD的派生类中检查是否有未设置")) //该check会将崩溃记录到日志
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass 没有选择值，请在AAuraHUD的派生类中检查是否有未设置"))
	//创建UI界面（就是屏幕上的血条、技能栏那套东西）
	UUserWidget* widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	//把创建出来的UI转成我们自定义的 Aura 基类控件
	OverlayWidget=Cast<UAuraUserWidget>(widget);
	// 把传进来的 4 个重要指针打包成一个“快递包”
	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	//创建一个 WidgetController（中间管理层）
	UOverlayWidgetController*WidgetController = GetOverlayWidgetController(WidgetControllerParams);//初始化一下控制层实例
	//把 WidgetController 交给 UI
	OverlayWidget->SetWidgetController(WidgetController);
	//35 在这里调用BoardcastIntailValues
	WidgetController->BroadcastInitailValues();
	
	widget->AddToViewport();
}


