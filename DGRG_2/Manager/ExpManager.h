// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Datas/DGRG_Macro.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerBase.h"
#include "ExpManager.generated.h"

/**
 * 
 */

class UDGRG_GameInstance;
UCLASS()
class DGRG_2_API UExpManager : public UManagerBase
{
	GENERATED_BODY()
public:
	UExpManager();
protected:
	UPROPERTY(VisibleAnywhere)
	int m_Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_MaxLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_Exp;

	int m_MaxExp;
public:
	virtual void Init(UDGRG_GameInstance* gameInstance) override;

	void SetMaxExp(int level);

	UFUNCTION(BlueprintCallable, Category = "Social")
	void IncreaseExp(int amount);
	UFUNCTION(BlueprintCallable, Category = "Social")
	void DecreaseExp(int amount);
	UFUNCTION(BlueprintCallable, Category = "Social")
	void SetExp(int value);
	UFUNCTION(BlueprintCallable, Category = "Social")
	int GetExp();
	UFUNCTION(BlueprintCallable, Category = "Social")
	int GetMaxExp();
	UFUNCTION(BlueprintCallable, Category = "Social")
	float GetExpOnePercent();
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidIntBP OnLevelUpN;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidVoidBP OnLevelUp;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidFloatBP OnExpChanged;

	int LevelUp();

	void NowMaxLevel();

};
