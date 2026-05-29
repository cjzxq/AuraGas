// cj.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURAGAS_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	//15.必须在子类实例化纯虚函数 现在敌人实现了这个接口，就可以在任何实现了这个接口的Actot上调用接口函数
	//可以设置AuraPlayerController中鼠标光标下的Actor  下面两个函数来自IEnemyInterface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
protected:
	virtual void BeginPlay() override;
};
