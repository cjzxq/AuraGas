// cj.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController:: BroadcastInitailValues()
{
	//34  Health Mana 等值广播给界面上的控件 创建几个委托（delegate）来广播
	//现在初始化 Health Mana等值，应该怎么获取？
	const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	//那什么时候调用广播初始值呢？ 应该在所有Widget的WidgetController设置好之后在调用
	//去看AuraHUD种看，因为创建有Widge和设置的WidgetControlle在里面的InitOverlay函数中
	
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	//只是要在这里绑定回调函数  这个函数应该在那里调用呢？
	//在AuraHUD中GetOverlayWidgetController这个函数中调用
	const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(
		this,& UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(
	this,& UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(
    this,& UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(
    this,& UOverlayWidgetController::MaxManaChanged);
}
//C++ 只负责把蓝量 / 血量数值广播抛出去，C++ 不能操作 UE 蓝图里的进度条控件，
//所以 UI 蓝图必须绑定委托、接收数值，去修改血条蓝条百分比。
//C++ 代码里找不到 WBP_ManaGlobe、找不到 ProgressBar 控件：

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)const
{

	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
