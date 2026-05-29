// cj.


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Auragas/Auragas.h"

AAuraEnemy::AAuraEnemy()
{
	//17.这些设置在蓝图中也可以，在c++中设置蓝图检查
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//20.AbilitySystemComponent是在AAuraCharacterBase定义的，UAuraAbilitySystemComponen是自己的类，继承自UAbilitySystemComponent
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//确保这个变量能被复制
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	//现在AbilitySystemComponent和AttributeSet有值了，
	//但是在AAuraCharacter中AbilitySystemComponent和AttributeSet还没有赋值
	//想在AuraPlayerState中设置这两个
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}

void AAuraEnemy::HighLightActor()
{
	//16.高亮敌人
	//高亮物体是通过后期处理材质，并且设置网格体渲染深度模板实现
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	//23 设置InitAbilityActorInfo，敌人类设置方法和Aura设置的方法不一样
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
