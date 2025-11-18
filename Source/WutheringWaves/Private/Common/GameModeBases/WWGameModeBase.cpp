// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/GameModeBases/WWGameModeBase.h"

#include "Common/PlayerControllers/WWPlayerController.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

AWWGameModeBase::AWWGameModeBase()
{
	bUseSeamlessTravel = true;
}

void AWWGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	AWWPlayerController* WWPC = Cast<AWWPlayerController>(NewPlayer);
	if (WWPC)
	{
		WWPC->SpawnAllCharacters();
		WWPC->Possess(WWPC->GetCurrentCharacter());
	}
}
