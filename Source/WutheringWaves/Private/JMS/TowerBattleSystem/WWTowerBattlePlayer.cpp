// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/WWTowerBattlePlayer.h"

// Sets default values
AWWTowerBattlePlayer::AWWTowerBattlePlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
void AWWTowerBattlePlayer::BroadcastOnBattleFailedDelegate()
{
	OnBattleFailed.Broadcast();
}

void AWWTowerBattlePlayer::BroadcastOnBattleClearedDelegate()
{
	OnBattleCleared.Broadcast();
}
