// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerBase.h"
#include "DGRG_Enum.h"
#include "DGRG_Struct.h"
#include "OptionManager.generated.h"

/**
 * 
 */
class UStoredEquipItem;
class UDGRG_GameInstance;
class UItemManager;
class UPlayerStatManager;
class UExpManager;
class UGoldManager;


UCLASS()
class DGRG_2_API UOptionManager : public UManagerBase
{
public:
	GENERATED_BODY()
	
	typedef void (UOptionManager::*FPtrOption)(const FOption&);
	typedef void (UOptionManager::*FPtrF)(float);
	UOptionManager();

public:
	virtual void Init(UDGRG_GameInstance* gameInstance) override;
public:
	void SetRandomOption(UStoredEquipItem* equipItem);
	
	void BindOptions();
	void EquipOptions(TArray<FOption>& option);
	void UnequipOptions(TArray<FOption>& option);
protected:
	UPROPERTY(VisibleAnywhere)
	UItemManager* m_ItemManager;
	UPROPERTY(VisibleAnywhere)
	UExpManager* m_ExpManager;
	UPROPERTY(VisibleAnywhere)
	UPlayerStatManager* m_PlayerStatManager;
	UPROPERTY(VisibleAnywhere)
	UGoldManager* m_GoldManager;
protected:
	FPtrF m_EquipOptionFPtrArray[(int)E_OPTIONTYPE::LENGTH];
	FPtrF m_UnequipOptionFPtrArray[(int)E_OPTIONTYPE::LENGTH];
	FPtrOption m_pAry_AddOption[(int)E_OPTIONTYPE::LENGTH];
	FPtrOption m_pAry_RemoveOption[(int)E_OPTIONTYPE::LENGTH];
protected:
	void SetOptionData(FOption & option, int lv, E_OPTIONTYPE optionType);
	void SetOptionRandomStatValue(FOption & option, const FOptionValueLevelData & OptionTable, int lv);
	float GetRandomV(const FOptionValue& value);
	TArray<int8>  OptionRandomArray(UStoredEquipItem * equipItem);
	void EquipOption(FOption & option);
	void UnequipOption(FOption & option);
protected:
#pragma region OptionAddRemove
	void Nothing(const FOption& value);
	void Add_HP_Per(const FOption& value);
	void Add_HP_Abs(const FOption& value);
	void Add_AS_Per(const FOption& value);
	void Add_AS_Abs(const FOption& value);
	void Add_MS_Per(const FOption& value);
	void Add_MS_Abs(const FOption& value);
	void Add_DMG_Per(const FOption& value);
	void Add_DMG_Abs(const FOption& value);
	void Add_AM_Per(const FOption& value);
	void Add_AM_Abs(const FOption& value);
	void Add_FM_Per(const FOption& value);
	void Add_FM_Abs(const FOption& value);
	void Add_EM_Per(const FOption& value);
	void Add_EM_Abs(const FOption& value);
	void Add_SM_Per(const FOption& value);
	void Add_SM_Abs(const FOption& value);
	void Add_EXS_Per(const FOption& value);
	void Add_DRR_Per(const FOption& value);
	void Add_GLDS_Per(const FOption& value);
	void Add_STR_Abs(const FOption& value);
	void Add_AGIL_Abs(const FOption& value);
	void Add_LUCK_Abs(const FOption& value);
	//
	void Remove_HP_Per(const FOption& value);
	void Remove_HP_Abs(const FOption& value);
	void Remove_AS_Per(const FOption& value);
	void Remove_AS_Abs(const FOption& value);
	void Remove_MS_Per(const FOption& value);
	void Remove_MS_Abs(const FOption& value);
	void Remove_DMG_Per(const FOption& value);
	void Remove_DMG_Abs(const FOption& value);
	void Remove_AM_Per(const FOption& value);
	void Remove_AM_Abs(const FOption& value);
	void Remove_FM_Per(const FOption& value);
	void Remove_FM_Abs(const FOption& value);
	void Remove_EM_Per(const FOption& value);
	void Remove_EM_Abs(const FOption& value);
	void Remove_SM_Per(const FOption& value);
	void Remove_SM_Abs(const FOption& value);
	void Remove_EXS_Per(const FOption& value);
	void Remove_DRR_Per(const FOption& value);
	void Remove_GLDS_Per(const FOption& value);
	void Remove_STR_Abs(const FOption& value);
	void Remove_AGIL_Abs(const FOption& value);
	void Remove_LUCK_Abs(const FOption& value);
#pragma endregion

};
