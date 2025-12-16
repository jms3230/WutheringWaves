// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Components/Combat/PawnCombatComponent.h"

#include "Common/Attack/AttackCollisionBox.h"
#include "Common/Attack/AttackCollisionBoxProjectile.h"
#include "Common/Attack/AttackCollisionCapsule.h"
#include "Common/Attack/AttackCollisionSphereProjectile.h"
#include "Common/ObjectPool/WWObjectPoolComponent.h"

void UPawnCombatComponent::OnHitTagetActor(AActor* HitActor)
{
	// 자식에서 구현
}

void UPawnCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	for (const FAttackCollisionPoolInfo& PoolInfo : AttackCollisionPools)
	{
		UWWObjectPoolComponent* NewPool;
		NewPool = NewObject<UWWObjectPoolComponent>(
			GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
		NewPool->PooledObjectClass = PoolInfo.AttackCollisionClass;
		NewPool->PoolSize = PoolInfo.PoolSize;
		NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
		NewPool->RegisterComponent();
		AttackCollisionPoolMap.Add(PoolInfo.AttackCollisionClass.Get(), NewPool);
	}
}
AActor* UPawnCombatComponent::EnableAttackCollisionByClass(TSubclassOf<AWWPooledObject> AttackCollisionClass)
{
	UWWObjectPoolComponent* Pool = AttackCollisionPoolMap.FindRef(AttackCollisionClass.Get());
	return Pool ? Pool->SpawnPooledObject(GetOwningPawn()) : nullptr;
}