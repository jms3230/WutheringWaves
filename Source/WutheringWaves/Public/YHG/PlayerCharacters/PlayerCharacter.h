// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Characters/WWCharacter.h"
#include "AbilitySystemInterface.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "PlayerCharacter.generated.h"

class UWWUserWidget;
class UPlayerCharacterStartup;
class UAttributeSet;
struct FGameplayTag;
class UAbilitySystemComponent;
class UPlayerCharacterAttributeSet;
class AEnemyCharacter;
class UCameraComponent;
class USpringArmComponent;


/**
 * 
 */

UCLASS()
class WUTHERINGWAVES_API APlayerCharacter : public AWWCharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	//IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPlayerCharacterAttributeSet* GetPlayerCharacterAttributeSet() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentHp(float CurrentHp);
	UFUNCTION(BlueprintCallable)
	float GetCurrentHp();

	UDataAsset_Startup* GetStartupData() const;

	UFUNCTION(BlueprintCallable)
	void SetEnabled(bool bIsEnabled);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UPawnUIComponent* PawnUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UWWAbilitySystemComponent* WWAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UPlayerCharacterAttributeSet* PlayerCharacterAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWWUserWidget* PlayerWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "PawnCombat", meta = (AllowPrivateAccess = "true"))
	UPawnCombatComponent* PawnCombatComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeAttributeSet(
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
		float CurrentConcertoEnergy, float MaxConcertoEnergy);

	UFUNCTION(BlueprintCallable)
	void ApplyWeaponStatsToCharacterAttributeSet(
	float ApplyAttack,
	float ApplyEnergyRegen,
	float ApplyCriticalRate
	);

	UFUNCTION(BlueprintCallable)
	void HealtoFullHP();
	
//StateControl
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsGrounded;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsFalling;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRun;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftJumping;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightJumping;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bCanAirDash;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bSprintMode;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bAttackMode;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	int32 DashCount;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	bool bDashInitCheck;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AbilityStateControl")
	int32 LightAttackComboCount;
public:
	UFUNCTION()
	bool GetIsGrounded() const;
	UFUNCTION()
	bool GetIsFalling() const;
	UFUNCTION()
	bool GetIsIdle() const;
	UFUNCTION()
	bool GetIsRightMoving() const;
	UFUNCTION()
	bool GetIsLeftMoving() const;
	UFUNCTION()
	bool GetIsRun() const;
	UFUNCTION()
	bool GetIsLeftJumping() const;
	UFUNCTION()
	bool GetIsRightJumping() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FSuccessGroundDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BSuccessGroundDash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* FAirDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* BAirDash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RFJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LFJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RFRunJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LFRunJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* RStopSprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerCharacterAnimation")
	UAnimMontage* LStopSprint;
};