// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_CheatManager.h"
#include "DGRG_PlayerCon.h"
#include "DGRG_GameInstance.h"
#include "ExpManager.h"
#include "ItemManager.h"
#include "ExpManager.h"
#include "GoldManager.h"
#include "PlayerStatManager.h"
#include "OptionManager.h"

UDGRG_CheatManager::UDGRG_CheatManager()
{
	m_PlayerCon = Cast<ADGRG_PlayerCon>(GetOuterAPlayerController());
	m_GameInstance = m_PlayerCon->GetGameInstance<UDGRG_GameInstance>();
}

UDGRG_CheatManager::UDGRG_CheatManager(const FObjectInitializer& ObjectInitializer)
{
	
}

void UDGRG_CheatManager::GiveExp(int v)
{
	m_PlayerCon = Cast<ADGRG_PlayerCon>(GetOuterAPlayerController());
	m_GameInstance = m_PlayerCon->GetGameInstance<UDGRG_GameInstance>();
	m_GameInstance->GetExpManager()->IncreaseExp(v);
}

void UDGRG_CheatManager::LevelUp(int lv)
{
	m_PlayerCon = Cast<ADGRG_PlayerCon>(GetOuterAPlayerController());
	m_GameInstance = m_PlayerCon->GetGameInstance<UDGRG_GameInstance>();
	while (lv>0)
	{
	m_GameInstance->GetExpManager()->LevelUp();
	lv--;
	}
}