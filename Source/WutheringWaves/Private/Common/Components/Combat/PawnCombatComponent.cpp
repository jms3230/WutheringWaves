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
	for (FAttackCollisionPoolInfo PoolInfo : AttackCollisionPools)
	{
		UWWObjectPoolComponent* NewPool;
		switch (PoolInfo.AttackCollisionType)
		{
		case EAttackCollisionType::Box:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionBox::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionBoxPool = NewPool;
			break;
		case EAttackCollisionType::SphereProjectile:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionSphereProjectile::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionSphereProjectilePool = NewPool;
			break;
		case EAttackCollisionType::BoxProjectile:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionBoxProjectile::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionBoxProjectilePool = NewPool;
			break;
		case EAttackCollisionType::Capsule:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionCapsule::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionCapsulePool = NewPool;
			break;
		default:
			break;
		}
	}
}

AAttackCollisionBox* UPawnCombatComponent::EnableAttackCollisionBoxFromPool()
{
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Instigator = GetOwningPawn();
	// AAttackCollisionBox* SpawnedCollisionBox = GetWorld()->SpawnActor<AAttackCollisionBox>(
	// 	AAttackCollisionBox::StaticClass(), FTransform::Identity,
	// 	SpawnParams);
	// FTimerHandle DespawnTimerHandle;
	// FTimerDelegate DespawnDelegate;
	// DespawnDelegate.BindLambda([=]()->void
	// {
	// 	if (IsValid(SpawnedCollisionBox))
	// 	{
	// 		SpawnedCollisionBox->K2_DestroyActor();
	// 	}
	// });
	// GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle,DespawnDelegate,10.f,false);
	// return SpawnedCollisionBox;
	return Cast<AAttackCollisionBox>(AttackCollisionBoxPool->SpawnPooledObject(GetOwningPawn()));
}

AAttackCollisionSphereProjectile* UPawnCombatComponent::EnableAttackCollisionSphereProjectileFromPool()
{
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Instigator = GetOwningPawn();
	// AAttackCollisionSphereProjectile* SpawnedCollisionSphereProjectile = GetWorld()->SpawnActor<AAttackCollisionSphereProjectile>(
	// 	AAttackCollisionSphereProjectile::StaticClass(), FTransform::Identity,
	// 	SpawnParams);
	// FTimerHandle DespawnTimerHandle;
	// FTimerDelegate DespawnDelegate;
	// DespawnDelegate.BindLambda([=]()->void
	// {
	// 	if (IsValid(SpawnedCollisionSphereProjectile))
	// 	{
	// 		SpawnedCollisionSphereProjectile->K2_DestroyActor();
	// 	}
	// });
	// GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle,DespawnDelegate,10.f,false);
	// return SpawnedCollisionSphereProjectile;
	return Cast<AAttackCollisionSphereProjectile>(AttackCollisionSphereProjectilePool->SpawnPooledObject(GetOwningPawn()));
}

AAttackCollisionBoxProjectile* UPawnCombatComponent::EnableAttackCollisionBoxProjectileFromPool()
{
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Instigator = GetOwningPawn();
	// AAttackCollisionBoxProjectile* SpawnedCollisionBoxProjectile = GetWorld()->SpawnActor<AAttackCollisionBoxProjectile>(
	// 	AAttackCollisionBoxProjectile::StaticClass(), FTransform::Identity,
	// 	SpawnParams);
	// FTimerHandle DespawnTimerHandle;
	// FTimerDelegate DespawnDelegate;
	// DespawnDelegate.BindLambda([=]()->void
	// {
	// 	if (IsValid(SpawnedCollisionBoxProjectile))
	// 	{
	// 		SpawnedCollisionBoxProjectile->K2_DestroyActor();
	// 	}
	// });
	// GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle,DespawnDelegate,10.f,false);
	// return SpawnedCollisionBoxProjectile;
	return Cast<AAttackCollisionBoxProjectile>(AttackCollisionBoxProjectilePool->SpawnPooledObject(GetOwningPawn()));
}

AAttackCollisionCapsule* UPawnCombatComponent::EnableAttackCollisionCapsuleFromPool()
{
	// FActorSpawnParameters SpawnParams;
	// SpawnParams.Instigator = GetOwningPawn();
	// AAttackCollisionCapsule* SpawnedCollisionCapsule = GetWorld()->SpawnActor<AAttackCollisionCapsule>(
	// 	AAttackCollisionCapsule::StaticClass(), FTransform::Identity,
	// 	SpawnParams);
	// FTimerHandle DespawnTimerHandle;
	// FTimerDelegate DespawnDelegate;
	// DespawnDelegate.BindLambda([=]()->void
	// {
	// 	if (IsValid(SpawnedCollisionCapsule))
	// 	{
	// 		SpawnedCollisionCapsule->K2_DestroyActor();
	// 	}
	// });
	// GetWorld()->GetTimerManager().SetTimer(DespawnTimerHandle,DespawnDelegate,10.f,false);
	// return SpawnedCollisionCapsule;
	return Cast<AAttackCollisionCapsule>(AttackCollisionCapsulePool->SpawnPooledObject(GetOwningPawn()));
}

void UPawnCombatComponent::DeactivateAllPooledObjects()
{
	if (AttackCollisionBoxPool)
	{
		AttackCollisionBoxPool->DeactivateAllPooledObjects();
	}
	if (AttackCollisionSphereProjectilePool)
	{
		AttackCollisionSphereProjectilePool->DeactivateAllPooledObjects();
	}
}
