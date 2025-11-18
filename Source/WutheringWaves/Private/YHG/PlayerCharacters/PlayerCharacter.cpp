// Fill out your copyright notice in the Description page of Project Settings.

#include "WutheringWaves/Public/YHG/PlayerCharacters/PlayerCharacter.h"

#include "Common/WWDebugHelper.h"

#include "Camera/CameraComponent.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "Common/PlayerStates/WWPlayerState.h"
#include "Common/Widget/WWUserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KMJ/UIComponents/PlayerUIComponent.h"
#include "YHG/AbilitySystem/PlayerCharacterAttributeSet.h"
#include "YHG/DataAssets/Startup/PlayerCharacterStartup.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//스프링암 초기세팅
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->bUsePawnControlRotation = true;

	//카메라 초기세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//케릭터움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	GetCharacterMovement()->JumpZVelocity = 840.0f;
	GetCharacterMovement()->GravityScale = 2.0f;

	//플레이어 UI 세팅
	PawnUI = CreateDefaultSubobject<UPawnUIComponent>(TEXT("PlayerUI"));;

	//플레이어 AttributeSet
	PlayerCharacterAttributeSet = CreateDefaultSubobject<UPlayerCharacterAttributeSet>(TEXT("ResonatorAttributeSet"));

	PawnCombatComponent = CreateDefaultSubobject<UPawnCombatComponent>(TEXT("PawnCombatComponent"));

	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	LightAttackComboCount = 1;
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	if (!GetPlayerState())
	{
		//Debug::Print(TEXT("PlayerCharacter : Can't Execute GetPlayerState()"),FColor::Red,451234);
		return nullptr;
	}
	return Cast<AWWPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
}

UPlayerCharacterAttributeSet* APlayerCharacter::GetPlayerCharacterAttributeSet() const
{
	return PlayerCharacterAttributeSet;
}

void APlayerCharacter::SetCurrentHp(float CurrentHp)
{
	PlayerCharacterAttributeSet->SetCurrentHp(CurrentHp);
}

float APlayerCharacter::GetCurrentHp()
{
	return PlayerCharacterAttributeSet->GetCurrentHp();
}

UDataAsset_Startup* APlayerCharacter::GetStartupData() const
{
	return StartupData.LoadSynchronous();
}

void APlayerCharacter::SetEnabled(bool bIsEnabled)
{
	if (bIsEnabled)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	}
	else
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	}

	//상태 정의 코드
	bIsGrounded = GetCharacterMovement()->IsMovingOnGround();
	bIsFalling = GetCharacterMovement()->IsFalling();
	//아무런 움직임이 없고, 지상일 때
	bIsIdle = GetCharacterMovement()->Velocity.IsZero() && bIsGrounded;

	//카메라 기준 오른쪽으로 움직이는지, 왼쪽으로 움직이는지
	FVector VelocityDirection = GetCharacterMovement()->Velocity.GetSafeNormal();
	bIsLeftMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCamera->GetForwardVector()).Z > 0;
	bIsRightMoving = UKismetMathLibrary::Cross_VectorVector(VelocityDirection, FollowCamera->GetForwardVector()).Z < 0;

	if ((bIsLeftMoving && bIsRightMoving) || (!bIsLeftMoving && !bIsRightMoving))
	{
		if (FMath::RandBool())
		{
			bIsLeftMoving = true;
			bIsRightMoving = false;
		}
		else
		{
			bIsLeftMoving = false;
			bIsRightMoving = true;
		}
	}

	//지상 움직임
	bIsRun = GetCharacterMovement()->GetCurrentAcceleration().SizeSquared2D() > 0.f && bIsGrounded;

	bIsLeftJumping = bIsLeftMoving && ((GetCharacterMovement()->Velocity.Z) > (GetCharacterMovement()->JumpZVelocity /
		2));
	bIsRightJumping = bIsRightMoving && ((GetCharacterMovement()->Velocity.Z) > (GetCharacterMovement()->JumpZVelocity /
		2));

	if (bIsGrounded)
	{
		bCanAirDash = true;
	}

	GetCharacterMovement()->MaxWalkSpeed = bSprintMode ? 600.0f : 450.0f;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/*WWAbilitySystemComponent = Cast<UWWAbilitySystemComponent>(GetAbilitySystemComponent());
	
	if (!StartupData.IsNull())
	{
		if (UDataAsset_Startup* LoadedData = StartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. 
			LoadedData->GiveToAbilitySystemComponent(WWAbilitySystemComponent);
		}
	}*/
	//초기설정
	
	
}

UPawnUIComponent* APlayerCharacter::GetPawnUIComponent() const
{
	return PawnUI;
}

void APlayerCharacter::InitializeAttributeSet(
	float CurrentHp, float MaxHp,
	float ApplyAttack, float BasicAttack,
	float ApplyDefense, float BasicDefense,
	float ApplyEnergyRegen, float BasicEnergyRegen,
	float ApplyCriticalRate, float BasicCriticalRate,
	float ApplyCriticalDamage, float BasicCriticalDamage,
	float CurrentSkillCoolTime, float MaxSkillCoolTime,
	float CurrentBurstCoolTime, float MaxBurstCoolTime,
	float CurrentBurstEnergy, float MaxBurstEnergy,
	float CurrentForteCircuitEnergy, float MaxForteCircuitEnergy,
	float CurrentConcertoEnergy, float MaxConcertoEnergy)
{
	PlayerCharacterAttributeSet->SetCurrentHp(CurrentHp);
	PlayerCharacterAttributeSet->SetMaxHp(MaxHp);
	
	PlayerCharacterAttributeSet->SetApplyAttack(ApplyAttack);
	PlayerCharacterAttributeSet->SetBasicAttack(BasicAttack);
	
	PlayerCharacterAttributeSet->SetApplyDefense(ApplyDefense);
	PlayerCharacterAttributeSet->SetBasicDefense(BasicDefense);
	
	PlayerCharacterAttributeSet->SetApplyEnergyRegen(ApplyEnergyRegen);
	PlayerCharacterAttributeSet->SetBasicEnergyRegen(BasicEnergyRegen);
	
	PlayerCharacterAttributeSet->SetApplyCriticalRate(ApplyCriticalRate);
	PlayerCharacterAttributeSet->SetBasicCriticalRate(BasicCriticalRate);
	
	PlayerCharacterAttributeSet->SetApplyCriticalDamage(ApplyCriticalDamage);
	PlayerCharacterAttributeSet->SetBasicCriticalDamage(BasicCriticalDamage);
	
	PlayerCharacterAttributeSet->SetCurrentSkillCoolTime(CurrentSkillCoolTime);
	PlayerCharacterAttributeSet->SetMaxSkillCoolTime(MaxSkillCoolTime);
	
	PlayerCharacterAttributeSet->SetCurrentBurstCoolTime(CurrentBurstCoolTime);
	PlayerCharacterAttributeSet->SetMaxBurstCoolTime(MaxBurstCoolTime);
	
	PlayerCharacterAttributeSet->SetCurrentBurstEnergy(CurrentBurstEnergy);
	PlayerCharacterAttributeSet->SetMaxBurstEnergy(MaxBurstEnergy);

	PlayerCharacterAttributeSet->SetCurrentForteCircuitEnergy(CurrentForteCircuitEnergy);
	PlayerCharacterAttributeSet->SetMaxForteCircuitEnergy(MaxForteCircuitEnergy);

	PlayerCharacterAttributeSet->SetCurrentConcertoEnergy(CurrentConcertoEnergy);
	PlayerCharacterAttributeSet->SetMaxConcertoEnergy(MaxConcertoEnergy);
}

void APlayerCharacter::ApplyWeaponStatsToCharacterAttributeSet(float ApplyAttack, float ApplyEnergyRegen,
	float ApplyCriticalRate)
{
	PlayerCharacterAttributeSet->SetApplyAttack(ApplyAttack);
	PlayerCharacterAttributeSet->SetApplyEnergyRegen(ApplyEnergyRegen);
	PlayerCharacterAttributeSet->SetApplyCriticalRate(ApplyCriticalRate);
}

void APlayerCharacter::HealtoFullHP()
{
	//Debug::Print(TEXT("HealToFullHP"));
	PlayerCharacterAttributeSet->SetCurrentHp(PlayerCharacterAttributeSet->GetMaxHp());
	GetPawnUIComponent()->OnCurrentHpValueChanged.Broadcast(PlayerCharacterAttributeSet->GetCurrentHp(), PlayerCharacterAttributeSet->GetMaxHp());
	GetPawnUIComponent()->OnCurrentHpChanged.Broadcast(PlayerCharacterAttributeSet->GetCurrentHp() / PlayerCharacterAttributeSet->GetMaxHp());
}

bool APlayerCharacter::GetIsGrounded() const
{
	return bIsGrounded;
}

bool APlayerCharacter::GetIsFalling() const
{
	return bIsFalling;
}


bool APlayerCharacter::GetIsIdle() const
{
	return bIsIdle;
}

bool APlayerCharacter::GetIsRightMoving() const
{
	return bIsRightMoving;
}

bool APlayerCharacter::GetIsLeftMoving() const
{
	return bIsLeftMoving;
}

bool APlayerCharacter::GetIsRun() const
{
	return bIsRun;
}

bool APlayerCharacter::GetIsLeftJumping() const
{
	return bIsLeftJumping;
}

bool APlayerCharacter::GetIsRightJumping() const
{
	return bIsRightJumping;
}
