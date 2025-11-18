// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/PlayerStates/WWPlayerState.h"
#include "Common/WWDebugHelper.h"
#include "YHG/AbilitySystem/PlayerStateAttributeSet.h"
#include "YHG/DataAssets/Startup/PlayerCharacterStartup.h"
#include "GameplayAbilitySpec.h"
#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

AWWPlayerState::AWWPlayerState()
{
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>("WWAbilitySystemComponent");
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerStateAttributeSet>(TEXT("PlayerAttributeSet"));
}

void AWWPlayerState::BeginPlay()
{
	Super::BeginPlay();

	OnPawnSet.AddDynamic(this, &ThisClass::ChangedPlayerCharacter);



	//교안 DA_ApplYEffecttoSelf


}

void AWWPlayerState::ChangedPlayerCharacter(APlayerState* Player, APawn* NewPawn, APawn* OldPawn)
{
	// if (!IsValid(NewPawn) || !IsValid(OldPawn))
	// {
	// 	Debug::Print(TEXT("WWPlayerState : InValid NewPawn or OldPawn"));
	// 	return;
	// }

	CancelAllPlayerActiveAbilities(WWAbilitySystemComponent);
	
	//Debug::Print(TEXT("AWWPlayerState::ChangedPlayerCharacter"));
	if (APlayerCharacter* OldPlayerCharacter = Cast<APlayerCharacter>(OldPawn))
	{
		WWAbilitySystemComponent->RemoveSpawnedAttribute(OldPlayerCharacter->GetPlayerCharacterAttributeSet());
	}
	//WWAbilitySystemComponent->SetAvatarActor(NewPawn);

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPawn))
	{
		WWAbilitySystemComponent->AddSpawnedAttribute(PlayerCharacter->GetPlayerCharacterAttributeSet());
		WWAbilitySystemComponent->InitAbilityActorInfo(this, PlayerCharacter);
	}
}

UAbilitySystemComponent* AWWPlayerState::GetAbilitySystemComponent() const
{
	return WWAbilitySystemComponent;
}


void AWWPlayerState::CancelPlayerActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag)
{
	if (!ASC || !CancelTag.IsValid())
	{
		//Debug::Print(TEXT("WWPlayerState : CancelPlayerActiveAbilities, Can't find ASC or CancelTag"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (!Spec.IsActive())
			continue;

		const UGameplayAbility* AbilityCDO = Spec.Ability;
		if (!AbilityCDO)
			continue;

		// 어빌리티에 태그가 포함되어 있으면
		if (AbilityCDO->AbilityTags.HasTagExact(CancelTag))
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}

void AWWPlayerState::CancelAllPlayerActiveAbilities(UAbilitySystemComponent* ASC)
{
	FScopedAbilityListLock ActiveScopeLock(*GetAbilitySystemComponent());
	if (!ASC)
	{
		//Debug::Print(TEXT("WWPlayerState : CancelAllActiveAbilities, Can't find ASC"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.IsActive())
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}
