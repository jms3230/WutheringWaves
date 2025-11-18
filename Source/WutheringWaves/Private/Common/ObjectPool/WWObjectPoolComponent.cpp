// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/ObjectPool/WWObjectPoolComponent.h"

#include "Common/ObjectPool/WWPooledObject.h"

// Sets default values
UWWObjectPoolComponent::UWWObjectPoolComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}

AWWPooledObject* UWWObjectPoolComponent::SpawnPooledObject(APawn* InInstigator)
{
	for (AWWPooledObject* PoolableActor : ObjectPool)
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true,InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}

	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		AWWPooledObject* PoolableActor = ObjectPool[PooledObjectIndex];
		if (PoolableActor != nullptr)
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true,InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}
	
	return nullptr;
}

void UWWObjectPoolComponent::OnPooledObjectDespawn(AWWPooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

void UWWObjectPoolComponent::DeactivateAllPooledObjects()
{
	while (SpawnedPoolIndexes.Num() > 0)
	{
		ObjectPool[SpawnedPoolIndexes[0]]->Deactivate();
	}
}

// Called when the game starts or when spawned
void UWWObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetOwner();
				AWWPooledObject* PoolableActor = World->SpawnActor<AWWPooledObject>(
					PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator,SpawnParams);
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false,nullptr);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UWWObjectPoolComponent::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
}
