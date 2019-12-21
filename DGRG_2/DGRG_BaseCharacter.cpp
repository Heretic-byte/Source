// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_BaseCharacter.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DGRG_GameInstance.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADGRG_BaseCharacter::ADGRG_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	m_IsDead = false;
	m_IsAttacking = false;
	//m_CharId = "Default";
	m_Timer = 0.0f;
	m_GameInstance = nullptr;
	m_CurrentLevel = 1;
	m_CurrentHealth = 100;
	m_ComboMax = 0;
	m_ComboCount = 0;
	m_IsHitten = false;
	GetMesh()->bUseAsOccluder = false;
}

float ADGRG_BaseCharacter::GetHpPercentOne()
{
	float PercentOne = 0.0f;

	if (m_CurrentHealth > 0)
	{
		PercentOne = m_CurrentHealth / m_StatFinal.m_HealthPoint.m_fFinalValue;
	}

	return	UKismetMathLibrary::FClamp(PercentOne, 0.0f, 1.0f);
}

void ADGRG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_GameInstance = GetGameInstance<UDGRG_GameInstance>();
}

void ADGRG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Timer += DeltaTime;
}

float ADGRG_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	m_IsHitten = true;
	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this,&ADGRG_BaseCharacter::SetHittenFalse, 0.6f, false);

	GetDamageToHealth(DamageAmount);
	return DamageAmount;
}

void ADGRG_BaseCharacter::SetHittenFalse()
{
	m_IsHitten = false;
}


FStatDefault * ADGRG_BaseCharacter::GetStatFinalPtr()
{
	return &m_StatFinal;
}

void ADGRG_BaseCharacter::OnHealthChangeBroadcast()
{
	auto PercentOne = GetHpPercentOne();

	OnHealthChangeBP.Broadcast(PercentOne);
	OnHealthChange.Broadcast(PercentOne);
}

bool ADGRG_BaseCharacter::GetIsHitten()
{
	return m_IsHitten;
}

int ADGRG_BaseCharacter::GetCurrentLevel() const
{
	return m_CurrentLevel;
}

void ADGRG_BaseCharacter::PauseAnim()
{
	GetAnimBP()->Montage_Pause(NULL);
}

void ADGRG_BaseCharacter::ResumeAnim()
{
	GetAnimBP()->Montage_Resume(NULL);
}



const FStatDefault &  ADGRG_BaseCharacter::GetStatFinal() const
{
	return m_StatFinal;
}

void ADGRG_BaseCharacter::SetCurrentHealth()
{
	m_CurrentHealth = GetStatFinal().m_HealthPoint.m_fFinalValue;
	OnHealthChangeBroadcast();
}

void ADGRG_BaseCharacter::GetDamageToHealth(float amount)
{
	m_CurrentHealth -= amount;

	OnHealthChangeBroadcast();

	if (m_CurrentHealth <= 0)
	{
		m_CurrentHealth = 0;
		GetKill();
		return;
	}

}

void ADGRG_BaseCharacter::GetHealToHealth(float amount)
{
	m_CurrentHealth += amount;

	if (m_CurrentHealth > GetStatFinal().m_HealthPoint.m_fFinalValue)
	{
		SetCurrentHealth();
		return;
	}

	OnHealthChangeBroadcast();
}

void ADGRG_BaseCharacter::GetKill()
{
	GetController()->UnPossess();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_IsDead = true;

	m_CurrentHealth = 0;

	FTimerHandle UnusedHandle;

	float deathAnimDur = PlayDeathMotion() - 0.3f;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADGRG_BaseCharacter::PauseAnim, deathAnimDur, false);

	OnGetKillBP.Broadcast();
}

void ADGRG_BaseCharacter::SetAttackingTrue()
{
	m_IsAttacking = true;
}

void ADGRG_BaseCharacter::SetAttackingFalse()
{
	m_IsAttacking = false;

}

void ADGRG_BaseCharacter::PlayAnim(int index)
{
	auto AnimInst = GetAnimBP();

	if (AnimInst->m_Motions.IsValidIndex(index))
	{
		PlayAnimMontage(AnimInst->m_Motions[index], 1.2f);//GetStatFinal().m_AttackSpeed
	}
	else
	{
		ResetCombo();
	}
}

bool ADGRG_BaseCharacter::TryAttack()
{
	if (m_IsAttacking)
	{
		return false;
	}

	if (m_Timer < 1 / GetStatFinal().m_AttackSpeed.m_fFinalValue)
	{
		return false;
	}

	m_Timer = 0.0f;

	PlayAnim(m_ComboCount);

	bool Result = m_ComboCount < m_ComboMax - 1;
	if (m_ComboMax > 0 && Result)
	{
		m_ComboCount++;
	}
	if (!Result)
	{
		ResetCombo();
	}


	return true;
}

float ADGRG_BaseCharacter::PlayDeathMotion()
{
	auto Anim = GetAnimBP();

	return PlayAnimMontage(Anim->m_DeathMotion, 1.0f);
}

UDGRG_HumanCharacter_AnimInstance * ADGRG_BaseCharacter::GetAnimBP()
{
	return Cast<UDGRG_HumanCharacter_AnimInstance>(GetMesh()->GetAnimInstance());;
}

void ADGRG_BaseCharacter::ResetCombo()
{
	//notifyShouldCall
	m_ComboCount = 0;
}

void ADGRG_BaseCharacter::SetMaxCombo(int comboMax)
{
	m_ComboMax = comboMax;
}

void ADGRG_BaseCharacter::SetActive(bool b)
{
	SetActorHiddenInGame(!b);

	SetActorEnableCollision(b);

	SetActorTickEnabled(b);

}



