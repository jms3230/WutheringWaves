// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWTowerBattlePlayer.generated.h"

class AWWWave;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleFailedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBattleClearedDelegate);

UCLASS()
class WUTHERINGWAVES_API AWWTowerBattlePlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWTowerBattlePlayer();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "TowerBattlePlayer")
	void OnTowerBattleStart();
	UFUNCTION(BlueprintCallable, Category = "TowerBattlePlayer")
	void BroadcastOnBattleFailedDelegate();
	UFUNCTION(BlueprintCallable, Category = "TowerBattlePlayer")
	void BroadcastOnBattleClearedDelegate();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "TowerBattlePlayer")
	TArray<TSubclassOf<AWWWave>> WavesToPlay;
protected:
	UPROPERTY(BlueprintAssignable)
	FOnBattleFailedDelegate OnBattleFailed;
	UPROPERTY(BlueprintAssignable)
	FOnBattleClearedDelegate OnBattleCleared;

};
