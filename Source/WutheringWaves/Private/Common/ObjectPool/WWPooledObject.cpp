// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/ObjectPool/WWPooledObject.h"
#include "Common/WWDebugHelper.h"

// Sets default values
AWWPooledObject::AWWPooledObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 0.f;
}

void AWWPooledObject::Deactivate()
{
	SetActive(false,nullptr);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
	SetActorHiddenInGame(true);
}

void AWWPooledObject::SetActive(bool IsActive, APawn* InInstigator)
{
	if(IsActive)
	{
		SetInstigator(InInstigator);
		GetWorldTimerManager().SetTimer(LifeTimeTimerHandle, this, &AWWPooledObject::Deactivate, LifeTime, false);
	}
	bIsActive = IsActive;
	SetActorHiddenInGame(!IsActive);
}

void AWWPooledObject::SetLifeTime(float InLifeTime)
{
	LifeTime = InLifeTime;
}

void AWWPooledObject::SetPoolIndex(int InIndex)
{
	PoolIndex = InIndex;
}

bool AWWPooledObject::IsActive()
{
	return bIsActive;
}

int AWWPooledObject::GetPoolIndex()
{
	return PoolIndex;
}
