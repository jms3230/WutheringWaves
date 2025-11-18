// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "Common/ObjectPool/WWPooledObject.h"
#include "AttackCollisionBox.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AAttackCollisionBox : public AWWPooledObject
{
	GENERATED_BODY()

	AAttackCollisionBox();

private:
	bool bIsAttached = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Components
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* BoxComponent;

	// AWWPooledObject
	virtual void SetActive(bool IsActive, APawn* InInstigator) override;
	virtual void Deactivate() override;

	// Attack
	UPROPERTY()
	TArray<AActor*> HitTargetArray;
	void OnHitTargetActor(AActor* HitActor);
	// 단일 이펙트 적용 함수를 위한 멤버변수
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	// 여러 이펙트 적용 함수를 위한 멤버변수
	TArray<FGameplayEffectSpecHandle> EffectsToApplyOnHitTarget;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse, const FHitResult& Hit);
	FGenericTeamId InstigatorTeamId;

	// FX
	FGameplayTag FXGameplayCueTag;

	FGameplayTag HitReactEventTag;
	// 시간으로 콜리전 활성화 조절
	void InitializeAndAttackWithBox_Internal(float Duration, FVector BoxExtent, FVector Location, FRotator Rotation,
									const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
									FGameplayTag InFXGameplayCueTag,
									FGameplayTag InHitReactEventTag);
	// Bone Socket에 붙여서 콜리전 활성화
	void InitializeAttachedBoxAndAttack_Internal(FVector BoxExtent, USkeletalMeshComponent* InstigatorMesh,
	                                             FName AttachSocketName,
	                                             const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
	                                             FGameplayTag InFXGameplayCueTag,
	                                             FGameplayTag InHitReactEventTag, bool bShowCollisionInGame = false,
	                                             float LineThickness = 5.0f);

	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box")
	void InitializeAndAttackWithBox(float Duration, FVector BoxExtent, FVector Location, FRotator Rotation,
	                                const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
	                                FGameplayTag InFXGameplayCueTag,
	                                FGameplayTag InHitReactEventTag);
	
	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box")
	void InitializeAttachedBoxAndAttack(FVector BoxExtent, USkeletalMeshComponent* InstigatorMesh,
	                                    FName AttachSocketName,
	                                    const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
	                                    FGameplayTag InFXGameplayCueTag,
	                                    FGameplayTag InHitReactEventTag, bool bShowCollisionInGame = false,
	                                    float LineThickness = 5.0f);

	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box")
	void InitializeAndAttackWithBoxMultipleEffects(float Duration, FVector BoxExtent, FVector Location, FRotator Rotation,
									const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
									FGameplayTag InFXGameplayCueTag,
									FGameplayTag InHitReactEventTag);

	// BP 호출용
	UFUNCTION(BlueprintCallable, Category = "Attack Box")
	void InitializeAttachedBoxAndAttackMultipleEffects(FVector BoxExtent, USkeletalMeshComponent* InstigatorMesh,
	                                                   FName AttachSocketName,
	                                                   const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
	                                                   FGameplayTag InFXGameplayCueTag,
	                                                   FGameplayTag InHitReactEventTag, bool bShowCollisionInGame = false,
	                                                   float LineThickness = 5.0f);
	UFUNCTION(BlueprintCallable, Category = "Attack Box")
	void DeactivateIfActivated();
};
