// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "MonsterBase.h"
#include "CoreMinimal.h"
#include "DungeonThemeAsset.h"
#include "UObject/NoExportTypes.h"
#include "DGRG_DungeonThemeAsset.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API UDGRG_DungeonThemeAsset : public UObject
{
	GENERATED_BODY()
	
public:
	UDGRG_DungeonThemeAsset();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon")
	UDungeonThemeAsset* m_DungeonTheme;
	UPROPERTY(EditDefaultsOnly,Category="Dungeon")
	TArray<TSubclassOf<AMonsterBase>> m_ThemeMonsterActors;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon")
	TSubclassOf<AMonsterBase> m_ThemeBossMonsterActor;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon")
	TAssetPtr<UWorld> m_BossLevel;
public:
	const TArray<TSubclassOf<AMonsterBase>>& GetThemeMobs() const;
	const TSubclassOf<AMonsterBase> GetThemeBossMob() const;
	const TAssetPtr<UWorld> GetBossLevel() const;
	 UDungeonThemeAsset* GetDungeonTheme() ;
};
