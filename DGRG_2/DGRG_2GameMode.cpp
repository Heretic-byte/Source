// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DGRG_2GameMode.h"
#include "TimerManager.h"

ADGRG_2GameMode::ADGRG_2GameMode()
{
	m_CurrentDungeonLevel = 1;
	m_CurrentDifficult = E_DIFFICULTY::EASY;
	m_CurrentSelectedTheme = nullptr;
	m_ClassDGDungeonActor = ADGRG_Dungeon::StaticClass();


	PrimaryActorTick.bCanEverTick = false;
}

void ADGRG_2GameMode::SelectDungeonLevel(int lvl)
{
	m_CurrentDungeonLevel = lvl;
}

void ADGRG_2GameMode::SelectDungeonDifficulty(E_DIFFICULTY diff)
{
	m_CurrentDifficult = diff;
}

void ADGRG_2GameMode::SelectDungeonTheme(int index)
{
	m_CurrentSelectedTheme = m_DungeonThemeArray[index];
}

UDGRG_DungeonThemeAsset * ADGRG_2GameMode::GetCurrentDgTheme()
{
	return m_CurrentSelectedTheme;
}

int ADGRG_2GameMode::GetCurrentLevel()
{
	return m_CurrentDungeonLevel;
}

E_DIFFICULTY ADGRG_2GameMode::GetCurrentDifficulty()
{
	return m_CurrentDifficult;
}

void ADGRG_2GameMode::CreateDungeon()
{
	PRINTF("Created Dungeon");
	m_DgActor->SetInstance(m_CurrentDungeonLevel, m_CurrentDifficult, m_CurrentSelectedTheme);
	PRINTF("Generate Dungeon");
	m_DgActor->GenerateDungeon();
}

void ADGRG_2GameMode::BeginPlay()
{
	m_DgActor = GetWorld()->SpawnActor<ADGRG_Dungeon>(m_ClassDGDungeonActor);

}
