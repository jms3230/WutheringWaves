// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackCollisionPoolInterface.generated.h"

class AWWPooledObject;
class AAttackCollisionCapsule;
class AAttackCollisionBoxProjectile;
class AAttackCollisionSphereProjectile;
class AAttackCollisionBox;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UAttackCollisionPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WUTHERINGWAVES_API IAttackCollisionPoolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category="Attack Collision Pool Interface", meta=(DeterminesOutputType = AttackCollisionClass))
	virtual AActor* EnableAttackCollisionByClass(TSubclassOf<AWWPooledObject> AttackCollisionClass) =0;
};
