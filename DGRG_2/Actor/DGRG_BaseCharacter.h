// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Character.h"
#include "DGRG_HumanCharacter_AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Datas/DataTableRowBase.h"


#include "Datas/DGRG_Struct.h"

#include "DGRG_BaseCharacter.generated.h"

class UDGRG_GameInstance;

UCLASS()
class DGRG_2_API ADGRG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidActorBP, AActor*, _interMan);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharDelegate, ADGRG_BaseCharacter*, character);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFStatChanged, const FStatDefault&, statDefault);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharStatChanged, const FStatChar&, statChar);
public:
	// Sets default values for this character's properties
	ADGRG_BaseCharacter(const FObjectInitializer& ObjectInitializer);
	//
#pragma region System

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, class AActor* DamageCauser) override;
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void SetActive(bool b);
#pragma endregion

#pragma region Animation
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PauseAnim();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResumeAnim();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void PlayAnim(int index);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual bool TryAttack();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	float PlayDeathMotion();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	UDGRG_HumanCharacter_AnimInstance* GetAnimBP();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetCombo();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetMaxCombo(int comboMax);
protected:
	float m_Timer;
	int m_ComboCount;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	int m_ComboMax;
#pragma endregion

#pragma region Status
public:
	void SetHittenFalse();
	FStatDefault* GetStatFinalPtr();
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int  GetCurrentLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FStatDefault&  GetStatFinal() const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool GetIsDead() { return m_IsDead; };
	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetHpPercentOne();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackingTrue();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackingFalse();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool GetIsHitten();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void GetKill();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnHealthChangeBroadcast();
public:
	FVoidFloat OnHealthChange;
public:
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FVoidFloatBP OnHealthChangeBP;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FVoidFloatBP OnStaminaChangeBP;
protected:
	FStatDefault m_StatFinal;//계산되는 마지막 스텟
	UDGRG_GameInstance* m_GameInstance;
	bool m_IsDead;
	bool m_IsHitten;
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Combat")
	int m_CurrentLevel;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Combat")
	bool m_IsAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float m_CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FDataTableRowHandle m_CharId;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FVoidVoidBP OnGetKillBP;

protected:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void GetDamageToHealth(float amount);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void GetHealToHealth(float amount);
public:
		UFUNCTION(BlueprintCallable, Category = "Combat")
		void SetCurrentHealthToMax();
	UFUNCTION(BlueprintCallable, Category = "Combat")
		FORCEINLINE float GetCurrentHealth() {
		return m_CurrentHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "Combat")
	FORCEINLINE  FDataTableRowHandle& GetCharID()
	{ 
		return  m_CharId;
	} 
#pragma endregion
};


