// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerBase.h"
#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "GoldManager.generated.h"

/**
 * 
 */

class UDGRG_GameInstance;
UCLASS()
class DGRG_2_API UGoldManager : public UManagerBase
{
	GENERATED_BODY()
public:
	UGoldManager();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_Gold;
public:
	UFUNCTION(BlueprintCallable, Category = "Social")
	void IncreaseGold(int amount);
	UFUNCTION(BlueprintCallable, Category = "Social")
	bool DecreaseGold(int amount);
	UFUNCTION(BlueprintCallable, Category = "Social")
	void SetGold(int value);
	UFUNCTION(BlueprintCallable, Category = "Social")
	int GetGold();
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidIntBP OnGoldChange;

	virtual void Init(UDGRG_GameInstance* gameInstance) override;
};
