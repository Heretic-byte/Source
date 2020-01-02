// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_CheatManager.h"
#include "Datas/DGRG_Macro.h"
#include "Actor/DGRG_PlayerCon.h"
#include "DGRG_GameInstance.h"
#include "ExpManager.h"
#include "ItemManager.h"
#include "ExpManager.h"
#include "GoldManager.h"
#include "PlayerStatManager.h"
#include "OptionManager.h"
#include "DungeonManager.h"
#include "Widgets/WidgetMasterCanvas.h"
#include "Widgets//WidgetDgMainEnter.h"
#include "Widgets/WidgetDgStageSelector.h"

void UDGRG_CheatManager::InitCheatManager()
{
	Super::InitCheatManager();
	SetInstance();
}

void UDGRG_CheatManager::SetInstance()
{
	m_PlayerCon = Cast<ADGRG_PlayerCon>(GetOuterAPlayerController());
	m_GameInstance = m_PlayerCon->GetGameInstance<UDGRG_GameInstance>();
}
void UDGRG_CheatManager::GiveExp(int v)
{
	m_GameInstance->GetExpManager()->IncreaseExp(v);
}

void UDGRG_CheatManager::IncreaseStatAttack(float v)
{
	m_GameInstance->GetPlayerStatManager()->IncreaseAbsDamage(v);
}

void UDGRG_CheatManager::IncreaseStatHp(float v)
{
	m_GameInstance->GetPlayerStatManager()->IncreaseAbsHp(v);
}

void UDGRG_CheatManager::IncreaseStatStr(float v)
{
	m_GameInstance->GetPlayerStatManager()->IncreaseBonusCharStat_Str(v);
}

void UDGRG_CheatManager::IncreaseGold(int v)
{
	m_GameInstance->GetGoldManager()->IncreaseGold(v);
}

void UDGRG_CheatManager::DecreaseGold(int v)
{
	if (!m_GameInstance->GetGoldManager()->DecreaseGold(v))
	{
		PRINTF("No gold sir");
	}
}

void UDGRG_CheatManager::PrintGold()
{
	PRINTF("Current Gold: %d", m_GameInstance->GetGoldManager()->GetGold());
}

void UDGRG_CheatManager::GenerateDungeon()
{
	PrintDungeonInfo();
	m_GameInstance->GetDungeonManager()->GenerateDungeon();
	PRINTF("DG GENERATE");
}

void UDGRG_CheatManager::PrintDungeonInfo()
{
	const UEnum* DiffyPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_DIFFICULTY"), true);
	E_DIFFICULTY Tye = m_GameInstance->GetDungeonManager()->GetCurrentDifficulty();
	FString Diffy=DiffyPtr->GetNameStringByValue((int)Tye);
	int Lv = m_GameInstance->GetDungeonManager()->GetCurrentLevel();
	FString ThemeName = m_GameInstance->GetDungeonManager()->GetCurrentTheme()->GetThemeName().ToString();
	PRINTF("Current Dungeon Difficulty: %s,Level: %d, Theme: %s",
		*Diffy,
		Lv,
		*ThemeName
	);
}

void UDGRG_CheatManager::SetDungeonDiffuculty(int eDiffy)
{
	m_GameInstance->GetDungeonManager()->SetDifficulty((E_DIFFICULTY)eDiffy);
}

void UDGRG_CheatManager::SetDungeonMobLevel(int lv)
{
	m_GameInstance->GetDungeonManager()->SetDungeonLevel(lv);
}

void UDGRG_CheatManager::SetDungeonTheme(int index)
{
	m_GameInstance->GetDungeonManager()->SetDungeonTheme(index);
}

void UDGRG_CheatManager::ClearDungeon()
{
	PRINTF("Clear DG");
	m_GameInstance->GetDungeonManager()->ClearCurrentDungeon();
}

void UDGRG_CheatManager::TeleportPlayerToDungeon()
{
	FVector Point = m_GameInstance->GetDungeonManager()->GetStartPoint();
	FRotator Rot(0,0,0);
	if (!m_PlayerCon->GetCharacter()->TeleportTo(Point, Rot))
	{
		PRINTF("Teleport - FAIL");
		return;
	}
	ShowFog();
	PRINTF("Teleport - SUCCESS");
}

void UDGRG_CheatManager::ShowFog()
{
	m_GameInstance->GetDungeonManager()->ShowFog();
}

void UDGRG_CheatManager::HideFog()
{
	m_GameInstance->GetDungeonManager()->HideFog();
}

void UDGRG_CheatManager::ResetMaterial()
{
	m_GameInstance->GetDungeonManager()->ReserFogMaterial();
}

void UDGRG_CheatManager::SetStageLevel(int lv)
{
	while (lv)
	{
		m_GameInstance->GetMasterCanvas()->GetDgEnter()->GetStageSelector()->IncreaseStageLevel();
		lv--;
	}
}

void UDGRG_CheatManager::LevelUp(int lv)
{
	SetInstance();
	while (lv>0)
	{
	m_GameInstance->GetExpManager()->LevelUp();
	lv--;
	}
}

