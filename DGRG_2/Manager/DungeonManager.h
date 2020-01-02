// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ManagerBase.h"
#include "Datas/DGRG_Enum.h"
#include "CoreMinimal.h"
#include "Actor/MonsterHordeManager.h"
#include "Core/Dungeon.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "DGRG_GameInstance.h"
#include "Datas/DGRG_Macro.h"
#include "DungeonManager.generated.h"

/**
 *
 */
class UGridDungeonQuery;
class UGridDungeonModel;
class UGridDungeonConfig;
class AFogOfWarManager;
class UDGRG_DungeonThemeAsset;
class ANavigationData;
/**
 * 
 */
UCLASS()
class DGRG_2_API UDungeonManager : public UManagerBase
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnThemeChanged, const UDGRG_DungeonThemeAsset*);

	UDungeonManager();
public:
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void GenerateDungeon();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void ClearCurrentDungeon();
	UFUNCTION()
	void OnNavCookComplete(ANavigationData* nav);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FVector GetStartPoint() const;
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FVector GetEndPoint() const;
public:
	void SetStartEndPoint();
	void SetGridPtrs();
	UDGRG_DungeonThemeAsset* GetCurrentTheme() const;
	int32 GetCurrentLevel() const;
	E_DIFFICULTY GetCurrentDifficulty() const;
	ADungeon* GetCurrentDungeonInstance()const;
	TSubclassOf<AMonsterHordeManager> GetCurrentHordeClass()const;
	int32 GetRoomCount()const;
	float GetDgSizeScale()const;
public:
	virtual void Init(UDGRG_GameInstance* gameInstance) override;
	void FindSetFogofWarActor();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SetDungeonLevel(int32 lvl);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SetDifficulty(E_DIFFICULTY diff);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void SetDungeonTheme(int index);
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void ShowFog();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void HideFog();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void ReserFogMaterial();
public:
	UPROPERTY(BlueprintAssignable)
	FVoidVoidBP m_OnDgBuildComplete;
	FOnThemeChanged m_OnThemeChanged;
protected:
	void SpawnDungeonMesh();
	void SpawnHordeManager(FVector location);
	void ClearHordeManagerAry();
	void BindOnNavComplete();
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CreateHordeInRoom();
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CreateHordeRandomCellLoca();
protected:
	UPROPERTY(BlueprintReadOnly)
	ADungeon* m_DungeonInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon", BlueprintReadOnly)
	TSubclassOf<AMonsterHordeManager> m_CMonsterHorde;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon", BlueprintReadOnly)
	TSubclassOf<ADungeon> m_CDungeon;
	UPROPERTY(EditDefaultsOnly, Category = "Dungeon", BlueprintReadOnly)
	TArray<UDGRG_DungeonThemeAsset*> m_TotalThemeAsset;
	UPROPERTY()
	UDGRG_DungeonThemeAsset* m_CurrentThemeAsset;
	UPROPERTY()
	TArray<AMonsterHordeManager*> m_HodeManagers;
	UPROPERTY()
	AFogOfWarManager* m_FogWarInLevel;
	
	
protected:
	float m_DungeonSizeScale;
	int32 m_CurrentLevel;
	int32 m_RoomCount;
	E_DIFFICULTY m_CurrentDifficulty;
	FVector m_StartRoom;
	FVector m_EndRoom;
	UGridDungeonModel* m_GridDgModel;
	UGridDungeonConfig* m_GridDgConfig;
	UGridDungeonQuery* m_GridQuery;
};
