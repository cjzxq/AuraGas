// cj.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURAGAS_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//14.想调用一个函数，当鼠标悬停在敌人上时，高亮显示敌人  两个接口函数 去AuraEnemy类中实现这个接口 
	virtual void HighLightActor()=0;//不会在这个类中提供定义，这个类被视为抽象类，从它的派生类中实现、
	virtual void UnHighLightActor()=0;
};
