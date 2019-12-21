// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldManager.h"
#include "DGRG_GameInstance.h"

void UGoldManager::Init(UDGRG_GameInstance * gameInstance)
{
	Super::Init(gameInstance);
}

UGoldManager::UGoldManager()
{
	m_Gold = 1000;

}

void UGoldManager::IncreaseGold(int amount)
{
	m_Gold += amount;

	if (m_Gold >(int)E_GLOBAL_CONST::MAXGOLD)
	{
		m_Gold = (int)E_GLOBAL_CONST::MAXGOLD;
	}
	OnGoldChange.Broadcast(m_Gold);
}

bool UGoldManager::DecreaseGold(int amount)
{
	if (m_Gold - amount < 0)
	{
		return false;
	}

	m_Gold -= amount;
	OnGoldChange.Broadcast(m_Gold);
	return true;
}

void UGoldManager::SetGold(int value)
{
	m_Gold = value;
	OnGoldChange.Broadcast(m_Gold);
}

int UGoldManager::GetGold()
{
	return m_Gold;
}

