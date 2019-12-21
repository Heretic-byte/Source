// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "DGRG_Enum.h"
#include "DGRG_Macro.h"
#include "DataTableRowBase.h"
#include "DGRG_DungeonThemeAsset.h"
#include "GameFramework/GameModeBase.h"
#include "DGRG_Dungeon.h"
#include "DGRG_2GameMode.generated.h"



UCLASS(minimalapi)
class ADGRG_2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADGRG_2GameMode();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon", BlueprintReadOnly)
	TSubclassOf<ADGRG_Dungeon> m_ClassDGDungeonActor;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon", BlueprintReadOnly)
	TArray<UDGRG_DungeonThemeAsset*> m_DungeonThemeArray;
public:
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CreateDungeon();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SelectDungeonLevel(int lvl);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SelectDungeonDifficulty(E_DIFFICULTY diff);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SelectDungeonTheme(int index);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	UDGRG_DungeonThemeAsset* GetCurrentDgTheme();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	int GetCurrentLevel();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	E_DIFFICULTY GetCurrentDifficulty();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FORCEINLINE ADGRG_Dungeon* GetDungeonManager() {return m_DgActor;}
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY()
	ADGRG_Dungeon* m_DgActor;
	UPROPERTY()
	UDGRG_DungeonThemeAsset* m_CurrentSelectedTheme;
	int m_CurrentDungeonLevel;
	E_DIFFICULTY m_CurrentDifficult;
};



