// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "DGRG_CheatManager.generated.h"

/**
 * 
 */

class UDGRG_GameInstance;
class ADGRG_PlayerCon;

UCLASS()
class DGRG_2_API UDGRG_CheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	ADGRG_PlayerCon* m_PlayerCon;
	UDGRG_GameInstance* m_GameInstance;
protected:
	virtual void InitCheatManager() override;
	void SetInstance();
public:
	UFUNCTION(exec)
	void LevelUp(int lv);
	UFUNCTION(exec)
	void GiveExp(int v);
	UFUNCTION(exec)
	void IncreaseStatAttack(float v);
	UFUNCTION(exec)
	void IncreaseStatHp(float v);
	UFUNCTION(exec)
	void IncreaseStatStr(float v);
	UFUNCTION(exec)
	void IncreaseGold(int v);
	UFUNCTION(exec)
	void DecreaseGold(int v);
	UFUNCTION(exec)
	void PrintGold();
	UFUNCTION(exec)
	void GenerateDungeon();
	UFUNCTION(exec)
	void PrintDungeonInfo();
	UFUNCTION(exec)
	void SetDungeonDiffuculty(int eDiffy);
	UFUNCTION(exec)
	void SetDungeonMobLevel(int lv);
	UFUNCTION(exec)
	void SetDungeonTheme(int index);
	UFUNCTION(exec)
	void ClearDungeon();
	UFUNCTION(exec)
	void TeleportPlayerToDungeon();
	UFUNCTION(exec)
	void ShowFog();
	UFUNCTION(exec)
	void HideFog();
	UFUNCTION(exec)
	void ResetMaterial();
	UFUNCTION(exec)
	void SetStageLevel(int lv);
};
