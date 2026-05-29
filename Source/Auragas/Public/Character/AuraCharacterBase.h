// cj.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)//这样就不会加入到关卡中
class AURAGAS_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	//22 下面两个函数返回指针 AuraEnemy中也设置了这两个变量 但是在AAuraCharacter没有，
	//因为设置在了AuraPlayerState中 后面会解决
	//IAbilitySystemInterface中的纯虚函数 所以在这里重写
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//希望角色有武器，所以添加一个基础网格组件，把组件附着在骨骼的插槽上，所以得确保骨骼有指定的插槽。.
	//1.创建一个武器，是骨骼网格组件的指针 TObjectPtr比原始指针多了跟踪（查看解引用）和延迟加载（不需要资产）的功能
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//19.创建两个指针， 玩家控制的角色要在player state中构造这些 
	//对于AuraEnemy来说，可以在对于AuraEnemy来说的构造函数中完成
	UPROPERTY()
	TObjectPtr <UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;
};
