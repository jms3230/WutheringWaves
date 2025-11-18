// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WWGameModeBase.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AWWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWWGameModeBase();
	

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
