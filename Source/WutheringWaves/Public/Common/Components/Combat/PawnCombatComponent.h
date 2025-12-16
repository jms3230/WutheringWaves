// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/WWPawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "Common/Interfaces/AttackCollisionPoolInterface.h"
#include "PawnCombatComponent.generated.h"

class UWWObjectPoolComponent;
class AAttackCollisionBox;
class AWWPooledObject;
class AWWObjectPool;

/**
 * 
 */
USTRUCT()
struct FAttackCollisionPoolInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWWPooledObject> AttackCollisionClass;
	UPROPERTY(EditAnywhere)
	int PoolSize = 20;
	UPROPERTY(EditAnywhere)
	float PooledObjectLifeTime = 20.0f;
};

UCLASS()
class WUTHERINGWAVES_API UPawnCombatComponent : public UWWPawnExtensionComponent, public IAttackCollisionPoolInterface
{
	GENERATED_BODY()
public:
	// 공격 처리
	virtual void OnHitTagetActor(AActor* HitActor);
	virtual void BeginPlay() override;

	//IAttackCollisionPoolInterface;
	virtual AActor* EnableAttackCollisionByClass(TSubclassOf<AWWPooledObject> AttackCollisionClass) override;
protected:
	//중복방지를 위한 배열
	TArray<AActor*> OverlappedActors;
	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision Pool")
	TArray<FAttackCollisionPoolInfo> AttackCollisionPools;
private:
	UPROPERTY(VisibleAnywhere)
	TMap<UClass*,UWWObjectPoolComponent*> AttackCollisionPoolMap;
};
