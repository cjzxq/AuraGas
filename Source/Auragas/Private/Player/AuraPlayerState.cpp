// cj.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//21 设置完这两个后，但是AAuraCharacter中这两个值还没有设置 指针是空的 去AAuraCharacterBase中看22
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//确保这个变量能被复制
	AbilitySystemComponent->SetIsReplicated(true);
	//Mixed总共三种模式Mixed full minimal(AI使用 看AAuraEnemy中代码) 
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//现在AbilitySystemComponent和AttributeSet有值了，
	//但是在AAuraCharacter中AbilitySystemComponent和AttributeSet还没有赋值
	//想在AuraPlayerState中
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	//18.设置网络更新频率 服务器尝试更新客户端的频率 任何需要同步的变量都会更新，
	//然后基于此类创建蓝图
	NetUpdateFrequency=100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
