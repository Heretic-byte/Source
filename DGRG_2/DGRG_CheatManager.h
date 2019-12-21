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
	UDGRG_CheatManager();
	UDGRG_CheatManager(const FObjectInitializer& ObjectInitializer);


	ADGRG_PlayerCon* m_PlayerCon;
	UDGRG_GameInstance* m_GameInstance;
public:
	UFUNCTION(exec)
	void LevelUp(int lv);
	UFUNCTION(exec)
	void GiveExp(int v);
};
