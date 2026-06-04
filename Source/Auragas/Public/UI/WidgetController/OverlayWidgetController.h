// cj.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuarWidgetController.h"
#include "OverlayWidgetController.generated.h"

//广播
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnhealthChangedSignature,float,Newhealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxhealthChangedSignature,float,NewMaxhealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);


/**
 * 
 */
//既是蓝图类型，也支持蓝图化
UCLASS(BlueprintType, Blueprintable)
class AURAGAS_API UOverlayWidgetController : public UAuarWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitailValues() override;
	virtual void BindCallBacksToDependencies() override;
	//可以在蓝图里绑定这个委托
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnhealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxhealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
protected:
	void HealthChanged(const FOnAttributeChangeData& Data)const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data)const;
	void ManaChanged(const FOnAttributeChangeData& Data)const;
	void MaxManaChanged(const FOnAttributeChangeData& Data)const;
};
