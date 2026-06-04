// cj.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAuraUserWidget;
class UAttributeSet;
struct  FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURAGAS_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	//28 显示控件 // 实例：运行时创建出来的对象
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController*GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC,APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS);
protected:

private:
	//存UI 的类 / 蓝图模板，是 “类引用” 告诉代码 “要创建哪种 UI”，后续用它来 CreateWidget。
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
