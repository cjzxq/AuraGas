// cj.


#include "UI/WidgetController/AuarWidgetController.h"
//30 这样WidgetController会自动设置成员变量
void UAuarWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController=WCParams.PlayerController;
	PlayerState=WCParams.PlayerState;
	AbilitySystemComponent=WCParams.AbilitySystemComponent;
	AttributeSet=WCParams.AttributeSet;
}

void UAuarWidgetController:: BroadcastInitailValues()
{
	
}

void UAuarWidgetController::BindCallBacksToDependencies()
{
	
}
