// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpManager.h"
#include "DGRG_GameInstance.h"
#include "Kismet/KismetMathLibrary.h"

UExpManager::UExpManager()
{
	m_Level = 1;
	m_MaxLevel = 50;
	m_Exp = 0;
	m_MaxExp = 0;
}

void UExpManager::Init(UDGRG_GameInstance* gameInstance)
{
	Super::Init(gameInstance);
	SetMaxExp(m_Level);
	SetExp(0);
}
void UExpManager::SetMaxExp(int level)
{
	m_MaxExp=m_GameInstance->GetExpTable(level).m_ExpNeed;
}

void UExpManager::IncreaseExp(int amount)
{
	if (m_MaxLevel <= m_Level)
	{
		return;
	}

	if (amount < 0)
	{
		PRINTF("Here");
	}

	m_Exp += amount;

	OnExpChanged.Broadcast(GetExpOnePercent());

	if (m_Exp >= m_MaxExp)
	{
		int RemainExp =  m_Exp- m_MaxExp;

		LevelUp();

		m_Exp = 0;

		if (RemainExp)
		{
		IncreaseExp(RemainExp);
		}
		else
		{
			OnExpChanged.Broadcast(GetExpOnePercent());
		}
	}
}

void UExpManager::DecreaseExp(int amount)
{
	m_Exp -= amount;

	if (m_Exp < 0)
	{
		m_Exp = 0;
	}

	OnExpChanged.Broadcast(GetExpOnePercent());
}

void UExpManager::SetExp(int value)
{
	m_Exp = value;
	OnExpChanged.Broadcast(GetExpOnePercent());
}

int UExpManager::GetExp()
{
	return m_Exp;
}

int UExpManager::GetMaxExp()
{
	return m_MaxExp;
}

float UExpManager::GetExpOnePercent()
{
	float PercentOne = 0.0f;
	float cExp = m_Exp;
	float mExp = m_MaxExp;
	if (m_Exp > 0)
	{
		PercentOne = cExp / mExp;
	}

	return UKismetMathLibrary::FClamp(PercentOne, 0.0f, 1.0f);
}

int UExpManager::LevelUp()
{
	if (m_Level >= (int)E_GLOBAL_CONST::MAXLEVEL)
	{
		NowMaxLevel();
		return m_Level;
	}

	m_Level++;
	OnLevelUp.Broadcast();
	OnLevelUpN.Broadcast(m_Level);
	SetMaxExp(m_Level);
	return m_Level;
}

void UExpManager::NowMaxLevel()
{
	m_Exp = 1;
	m_MaxExp = 1;
}


