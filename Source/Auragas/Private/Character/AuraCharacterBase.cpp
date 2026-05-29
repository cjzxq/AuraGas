// cj.


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;//目前不需要实时更新
	//2.创建骨骼组件   UObject 架构的专属工厂函数 分配内存 调用构造函数 初始化 UObject 基础结构
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//3.把武器装到网格上得一个插槽里 把武器装在WeaponHandSocket这个插槽中
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	//4.武器不该有碰撞 只是视觉模型，否则武器会和角色自身身体疯狂碰撞 现在创建蓝图，就会有Weapon组建了，现在去创建蓝图（针对AuraCharacter类），//
	//角色和敌人蓝图创建完后再去创建动画 然后下一步是处理输入了 //
	//处理输入之后，现在需要把数据连接到角色，可以在角色类中写，但是为了管理，写在AuraPlayerController类中,然后去AuraPlayerController中
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



