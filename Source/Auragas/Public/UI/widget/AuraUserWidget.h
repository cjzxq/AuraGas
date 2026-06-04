// cj.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
//27 所有的UserWidget都将基于这个类创建蓝图
//UserWidget负责Widget的视觉表现 接受数据后，在Widget中呈现效果
UCLASS()
class AURAGAS_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject>WidgetController;
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject*InWidgetController);
protected:
	// 蓝图可实现事件（只声明，不实现） 
	UFUNCTION( BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
