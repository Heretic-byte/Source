// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_DungeonThemeAsset.h"

UDGRG_DungeonThemeAsset::UDGRG_DungeonThemeAsset()
{
	m_DungeonTheme = nullptr;
}

const TArray<TSubclassOf<AMonsterBase>>& UDGRG_DungeonThemeAsset::GetThemeMobs() const
{
	return m_ThemeMonsterActors;
}

const TSubclassOf<AMonsterBase> UDGRG_DungeonThemeAsset::GetThemeBossMob() const
{
	return m_ThemeBossMonsterActor;
}

const TAssetPtr<UWorld> UDGRG_DungeonThemeAsset::GetBossLevel() const
{
	return m_BossLevel;
}

 UDungeonThemeAsset * UDGRG_DungeonThemeAsset::GetDungeonTheme() 
{
	return m_DungeonTheme;
}
