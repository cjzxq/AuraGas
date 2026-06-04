// cj.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURAGAS_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	//24 设置Aura的InitAbilityActorInfo 重写下面两个函数
	virtual void PossessedBy(AController*NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
	
};
