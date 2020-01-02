// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionManager.h"
#include "DGRG_GameInstance.h"
#include "ItemManager.h"
#include "ExpManager.h"
#include "GoldManager.h"
#include "PlayerStatManager.h"
#include "Math/UnrealMathUtility.h"

UOptionManager::UOptionManager()
{
	BindOptions();
}

void UOptionManager::Init(UDGRG_GameInstance * gameInstance)
{
	Super::Init(gameInstance);
	m_ExpManager = m_GameInstance->GetExpManager();
	m_ItemManager = m_GameInstance->GetItemManager();
	m_PlayerStatManager = m_GameInstance->GetPlayerStatManager();
	m_GoldManager = m_GameInstance->GetGoldManager();
	//
	
}

void UOptionManager::SetRandomOption(UStoredEquipItem * equipItem)
{
	auto NumberArray= OptionRandomArray(equipItem);//해당 아이템이 가질수있는 옵션 랜덤선택
	auto& DataTableOptionArray = equipItem->GetEquipItemData().m_Options;//데이터 테이블
	auto& StoredEquipItemOptionArray=equipItem->GetOptionArrays();//아이템의 옵션칸

	int ItemOptionCount = DataTableOptionArray.Num();
	int OptionCount = FMath::RandRange(0, (int)equipItem->GetItemTier().m_TierName+1);

	if (ItemOptionCount < OptionCount)
	{
		OptionCount = ItemOptionCount;
	}

	StoredEquipItemOptionArray.Reserve(OptionCount);//티어 등급곗수만큼 랜덤 칸생성

	for (int i = 0; i < OptionCount; i++)
	{
		E_OPTIONTYPE SelectedOption = DataTableOptionArray[NumberArray[i]];
		FOption NewOption;
		if(SelectedOption!=E_OPTIONTYPE::NONE)
		{
			SetOptionData(NewOption, equipItem->GetItemLevel(),SelectedOption);
		}
		StoredEquipItemOptionArray.Emplace(NewOption);
	}
}

void UOptionManager::EquipOption(FOption & option)
{
	(this->*m_pAry_AddOption[(int)option.m_OptionType])(option);
}

void UOptionManager::UnequipOption(FOption & option)
{
	(this->*m_pAry_RemoveOption[(int)option.m_OptionType])(option);
}

void UOptionManager::BindOptions()
{
	m_pAry_AddOption[(int)E_OPTIONTYPE::NONE]   = &UOptionManager::Nothing;
	m_pAry_AddOption[(int)E_OPTIONTYPE::HP_Per] = &UOptionManager::Add_HP_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::HP_Abs] = &UOptionManager::Add_HP_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::AS_Per] = &UOptionManager::Add_AS_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::AS_Abs] = &UOptionManager::Add_AS_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::MS_Per] = &UOptionManager::Add_MS_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::MS_Abs] = &UOptionManager::Add_MS_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::DMG_Per] = &UOptionManager::Add_DMG_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::DMG_Abs] = &UOptionManager::Add_DMG_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::AM_Per] = &UOptionManager::Add_AM_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::AM_Abs] = &UOptionManager::Add_AM_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::FM_Per] = &UOptionManager::Add_FM_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::FM_Abs] = &UOptionManager::Add_FM_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::EM_Per] = &UOptionManager::Add_EM_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::EM_Abs] = &UOptionManager::Add_EM_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::SM_Per] = &UOptionManager::Add_SM_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::SM_Abs] = &UOptionManager::Add_SM_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::EXS_Per] = &UOptionManager::Add_EXS_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::DRR_Per] = &UOptionManager::Add_DRR_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::GLDS_Per] = &UOptionManager::Add_GLDS_Per;
	m_pAry_AddOption[(int)E_OPTIONTYPE::STR_Abs] = &UOptionManager::Add_STR_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::AGIL_Abs] = &UOptionManager::Add_AGIL_Abs;
	m_pAry_AddOption[(int)E_OPTIONTYPE::LUCK_Abs] = &UOptionManager::Add_LUCK_Abs;
	//
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::NONE] = &UOptionManager::Nothing;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::HP_Per] = &UOptionManager::Remove_HP_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::HP_Abs] = &UOptionManager::Remove_HP_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::AS_Per] = &UOptionManager::Remove_AS_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::AS_Abs] = &UOptionManager::Remove_AS_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::MS_Per] = &UOptionManager::Remove_MS_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::MS_Abs] = &UOptionManager::Remove_MS_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::DMG_Per] = &UOptionManager::Remove_DMG_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::DMG_Abs] = &UOptionManager::Remove_DMG_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::AM_Per] = &UOptionManager::Remove_AM_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::AM_Abs] = &UOptionManager::Remove_AM_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::FM_Per] = &UOptionManager::Remove_FM_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::FM_Abs] = &UOptionManager::Remove_FM_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::EM_Per] = &UOptionManager::Remove_EM_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::EM_Abs] = &UOptionManager::Remove_EM_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::SM_Per] = &UOptionManager::Remove_SM_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::SM_Abs] = &UOptionManager::Remove_SM_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::EXS_Per] = &UOptionManager::Remove_EXS_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::DRR_Per] = &UOptionManager::Remove_DRR_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::GLDS_Per] = &UOptionManager::Remove_GLDS_Per;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::STR_Abs] = &UOptionManager::Remove_STR_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::AGIL_Abs] = &UOptionManager::Remove_AGIL_Abs;
	m_pAry_RemoveOption[(int)E_OPTIONTYPE::LUCK_Abs] = &UOptionManager::Remove_LUCK_Abs;
}

void UOptionManager::EquipOptions(TArray<FOption>& option)
{
	for (auto& OptionV : option)
	{
		EquipOption(OptionV);
	}
}

void UOptionManager::UnequipOptions(TArray<FOption>& option)
{
	for (auto& OptionV : option)
	{
		UnequipOption(OptionV);
	}
}

TArray<int8> UOptionManager::OptionRandomArray(UStoredEquipItem * equipItem)
{
	int8  MaxOptionCount = equipItem->GetEquipItemData().m_Options.Num();
	int8  MaxOptionCountRandRange = MaxOptionCount - 1;
	TArray<int8> NumberArray;
	NumberArray.Reserve(MaxOptionCount);
	for (int8 i = 0; i < MaxOptionCount; i++)
	{
		NumberArray.Emplace(i);
	}
	for (int8 i = 0; i < MaxOptionCount; i++)
	{
		int8 RandomIndex = FMath::RandRange(0, MaxOptionCountRandRange);
		int8 Temp = NumberArray[i];
		NumberArray[i] = NumberArray[RandomIndex];
		NumberArray[RandomIndex] = Temp;
	}

	return NumberArray;
}

#pragma region OptionAddRemove
void UOptionManager::Nothing(const FOption & value)
{
	//dont do anything
}

void UOptionManager::Add_HP_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerHp(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_HP_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsHp(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_AS_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerAttackSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_AS_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsAttackSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_MS_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerMoveSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_MS_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsMoveSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_DMG_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerDamage(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_DMG_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsDamage(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_AM_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_AM_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_FM_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerFireArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_FM_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseAbsFireArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_EM_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerElecArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_EM_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreasePerElecArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_SM_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerElecArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_SM_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreasePerSoulArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_EXS_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerExpScale(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_DRR_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerDropRate(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_GLDS_Per(const FOption & value)
{
	m_PlayerStatManager->IncreasePerGoldScale(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_STR_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseBonusCharStat_Str(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_AGIL_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseBonusCharStat_Agil(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Add_LUCK_Abs(const FOption & value)
{
	m_PlayerStatManager->IncreaseBonusCharStat_Luck(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_HP_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerHp(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_HP_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsHp(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_AS_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerAttackSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_AS_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsAttackSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_MS_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerMoveSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_MS_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsMoveSpeed(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_DMG_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerDamage(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_DMG_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsDamage(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_AM_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_AM_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_FM_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerFireArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_FM_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsFireArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_EM_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerElecArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_EM_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsElecArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_SM_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerSoulArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_SM_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseAbsSoulArmor(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_EXS_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerExpScale(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_DRR_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerDropRate(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_GLDS_Per(const FOption & value)
{
	m_PlayerStatManager->DecreasePerGoldScale(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_STR_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseBonusCharStat_Str(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_AGIL_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseBonusCharStat_Agil(value.m_OptionValue.GetFinalValue());
}

void UOptionManager::Remove_LUCK_Abs(const FOption & value)
{
	m_PlayerStatManager->DecreaseBonusCharStat_Luck(value.m_OptionValue.GetFinalValue());
}
#pragma endregion

void UOptionManager::SetOptionData(FOption & option, int lv,E_OPTIONTYPE optionType)
{	
	const FOptionValueLevelData& OptionTable = m_GameInstance->GetOptionValue(optionType);
	option.SetOptionType(optionType);
	SetOptionRandomStatValue(option, OptionTable, lv);
	option.SetIsPercValue(OptionTable.m_IsPercValue);
	option.SetOptionName(OptionTable.m_OptionName);
}

void UOptionManager::SetOptionRandomStatValue(FOption & option, const FOptionValueLevelData & OptionTable, int lv)
{
	option.SetStatValue(GetRandomV(OptionTable.m_OptionValue[lv]));
}

float UOptionManager::GetRandomV(const FOptionValue& value)
{
	return FMath::RandRange(value.m_MinValue, value.m_MaxValue);
}
