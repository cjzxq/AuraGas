// cj.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class AURAGAS_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
	/*//26 在游戏中吃到什么东西 如何改变属性 先用下面两个函数代替
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent*OverlappedComponent,AActor*OtherActor,UPrimitiveComponent*OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent*OverlappedComponent, AActor*OtherActor, UPrimitiveComponent*OtherComp, int32 OtherBodyIndex);
*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	//39
	void ApplyEffectToTarget(AActor*Target,TSubclassOf<UGameplayEffect>GamePlayEffectClass);
	//38 用于实现即实效果的类
	UPROPERTY(EditAnywhere,Category="Applied Effects")
	TSubclassOf<UGameplayEffect>InstantGamePlayEffectClass;
private:
	/*
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Mesh;
	*/
};
