// cj.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	//13.设置参数，让角色正常移动
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;//运动将限制在一个平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;//运动开始时与平面对齐
	//不使用控制器的旋转
	bUseControllerRotationPitch = false; 
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//InitAbilityActorInfo给服务器使用 注意InitAbilityActorInfo中两给参数
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//给客户端使用
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	
	//AbilitySystemComponent和AttributeSet也通过AuraPlayerState来设置 这些指针设置在服务器上
	AAuraPlayerState*AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//32 在这里初始化 HUD通过 PlayerController来获取 所以需要先拿到PlayerController来获取
	//HUD 属于 PlayerController HUD 永远不用自己创建 获取 HUD 唯一正确方式：PC->GetHUD ()
	//PlayerController可能为空，因为在多人游戏中，只有服务端拥有全部的PlayerController，客户端只有自己的，没有其他的PlayerController
	//所以在这里是检查指针，而不是check
	if (AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
	{
		 if (AAuraHUD*AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		 {
		 	AuraHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		 }
	}
	
}
