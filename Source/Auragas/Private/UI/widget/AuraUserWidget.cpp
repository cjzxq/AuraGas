// cj.


#include "UI/widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();// C++调用，触发蓝图Event WidgetControllerSet
}
