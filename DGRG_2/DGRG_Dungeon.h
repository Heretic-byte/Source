// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_Enum.h"
#include "DGRG_DungeonThemeAsset.h"
#include "CoreMinimal.h"
#include "MonsterHordeManager.h"
#include "Core/Dungeon.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "DGRG_GameInstance.h"
#include "DGRG_Dungeon.generated.h"

/**
 * 
 */


class ANavigationData;

UCLASS()
class DGRG_2_API ADGRG_Dungeon : public AActor
{
	GENERATED_BODY()
public:
	ADGRG_Dungeon();
public:
	UFUNCTION(BlueprintCallable,Category = "Dungeon")
	void SetInstance(int32 playerLevel, E_DIFFICULTY diff,  UDGRG_DungeonThemeAsset* dgTheme);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void GenerateDungeon();

	UDGRG_DungeonThemeAsset* GetCurrentTheme();
	int32 GetCurrentLevel();
	E_DIFFICULTY GetCurrentDifficulty();
	ADungeon* GetCurrentDungeonInstance();
	TSubclassOf<AMonsterHordeManager> GetCurrentHordeClass();
	int32 GetRoomCount();
	float GetDgSizeScale();
protected:
	void SetDungeonLevel(int32 lvl);
	void SetDifficulty(E_DIFFICULTY diff);
	void SetDungeonTheme( UDGRG_DungeonThemeAsset* dgTheme);

	void SpawnDungeonMesh();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CreateHordeInRoom();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CreateHordeRandomCellLoca();
	void SpawnHordeManager(FVector location);

	virtual void BeginPlay() override;

	void ClearCurrentDungeon();

	//
public:
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void OnDungeonBuildComplete(ADungeon* dg);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void OnNavCookComplete(ANavigationData* nav);
public:
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FVector GetStartPoint();

protected:
	UPROPERTY(BlueprintReadOnly)
	ADungeon* m_DungeonInstance;

	int32 m_CurrentLevel;
	E_DIFFICULTY m_CurrentDifficulty;
	UPROPERTY()
	UDGRG_DungeonThemeAsset* m_CurrentThemeAsset;

	UPROPERTY(EditDefaultsOnly,Category="Dungeon", BlueprintReadOnly)
	TSubclassOf<AMonsterHordeManager> m_MonsterHordeClass;

	float m_DungeonSizeScale;
	int32 m_RoomCount;
	UPROPERTY()
	UDGRG_GameInstance* m_GameInstance;

};
