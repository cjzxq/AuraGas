// cj.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)//这样就不会加入到关卡中
class AURAGAS_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//希望角色有武器，所以添加一个基础网格组件，把组件附着在骨骼的插槽上，所以得确保骨骼有指定的插槽。.
	//1.创建一个武器，是骨骼网格组件的指针 TObjectPtr比原始指针多了跟踪（查看解引用）和延迟加载（不需要资产）的功能
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
