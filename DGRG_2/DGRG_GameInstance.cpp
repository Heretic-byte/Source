// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_GameInstance.h"
//
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
//
#include "Delegate.h"
//
#include "DGRG_CombatCharacter.h"
#include "MonsterBase.h"
#include "GoldManager.h"
#include "ExpManager.h"
#include "ItemManager.h"
#include "OptionManager.h"
//
#include "PlayerStatManager.h"
#include "DGRG_DungeonThemeAsset.h"
#include "DroppedItemActor.h"
#include "StoredItem.h"

UDGRG_GameInstance::UDGRG_GameInstance()
{
	m_ItemTierEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_ITEMTIER"), true);
	m_DifficultyEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_DIFFICULTY"), true);
	m_OptionTypeEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_OPTIONTYPE"), true);
	
}

void UDGRG_GameInstance::Init()
{
	Super::Init();
	//인자값에 템플릿을 안주면 프로퍼티 변경사항이 적용이안됨
	m_GoldManager = NewObject<UGoldManager>(m_CGoldManager, NAME_None, RF_NoFlags, m_CGoldManager->GetDefaultObject<UGoldManager>());
	m_ExpManager = NewObject<UExpManager>( m_CExpManager, NAME_None, RF_NoFlags, m_CExpManager->GetDefaultObject<UExpManager>());
	m_ItemManager = NewObject<UItemManager>( m_CItemManager,NAME_None,RF_NoFlags, m_CItemManager->GetDefaultObject<UItemManager>());
	m_PlayerStatManager = NewObject<UPlayerStatManager>( m_CPlayerStatManager, NAME_None, RF_NoFlags, m_CPlayerStatManager->GetDefaultObject<UPlayerStatManager>());
	m_OptionManager = NewObject<UOptionManager>(m_COptionManager, NAME_None, RF_NoFlags, m_COptionManager->GetDefaultObject<UOptionManager>());
	//
	//여기서 셋
	m_GoldManager->Init(this);
	m_ExpManager->Init(this);
	m_ItemManager->Init(this);
	m_PlayerStatManager->Init(this);
	m_OptionManager->Init(this);
	//
	m_ExpManager->OnLevelUp.AddDynamic(m_PlayerStatManager, &UPlayerStatManager::GainStatLevelUp);

	PRINTF("Manager Init Done");
}

#pragma region DataGetter


const FBaseItemData & UDGRG_GameInstance::GetBaseItemData(FName id) const
{
	return *m_BaseItemDB->FindRow<FBaseItemData>(id, "");
}

const FMaterialItemData & UDGRG_GameInstance::GetMaterialItemData(FName id) const
{
	return *m_MaterialItemDB->FindRow<FMaterialItemData>(id, "");
}

const FEquipmentItemData & UDGRG_GameInstance::GetEquipItemData(FName id) const
{
	return *m_EquipItemDB->FindRow<FEquipmentItemData>(id, "");
}

const FItemTier & UDGRG_GameInstance::GetItemTier(E_ITEMTIER itemTier) const
{
	FName id = m_ItemTierEnumPtr->GetNameByIndex((int)itemTier);


	return *m_ItemTierTable->FindRow<FItemTier>(id, "");
}

const FOptionValueLevelData & UDGRG_GameInstance::GetOptionValue(E_OPTIONTYPE opType) const
{
	FName id = m_OptionTypeEnumPtr->GetNameByIndex((int)opType);

	return *m_OptionTable->FindRow<FOptionValueLevelData>(id, "");
}

const FMonsterStatTable & UDGRG_GameInstance::GetMonsterStat(FName id) const
{
	return  *m_MonsterStatDB->FindRow<FMonsterStatTable>(id, "");
}

const FExpTable & UDGRG_GameInstance::GetExpTable(int id) const
{
	return *m_ExpTable->FindRow<FExpTable>(FName(*(FString::FromInt(id))), "");
}

const FTierScaleStatPerc & UDGRG_GameInstance::GetMonsterNamedScale(E_ITEMTIER itemTier) const
{
	FName id = m_ItemTierEnumPtr->GetNameByIndex((int)itemTier);
	return *m_MonsterNamedScaleTable->FindRow<FTierScaleStatPerc>(id, "");
}

const FScaleStatPercTable & UDGRG_GameInstance::GetDifficultyScale(E_DIFFICULTY diff) const
{
	FName id = m_DifficultyEnumPtr->GetNameByIndex((int)diff);
	return *m_DifficultyScaleTable->FindRow<FScaleStatPercTable>(id, "");
}

const FHumanStatTable & UDGRG_GameInstance::GetHumanStat(FName id) const
{
	return *m_HumanStatDB->FindRow<FHumanStatTable>(id, "");
}

const FFloatTable & UDGRG_GameInstance::GetDungeonLevelScale(int level) const
{
	if (level < 12)
	{
		return *m_DungeonSizeLevelScale->FindRow<FFloatTable>(FName(*(FString::FromInt(1))), "");
	}
	else if (level < 24)
	{
		return *m_DungeonSizeLevelScale->FindRow<FFloatTable>(FName(*(FString::FromInt(2))), "");
	}
	else if (level < 36)
	{
		return *m_DungeonSizeLevelScale->FindRow<FFloatTable>(FName(*(FString::FromInt(3))), "");
	}
	else if (level < 48)
	{
		return *m_DungeonSizeLevelScale->FindRow<FFloatTable>(FName(*(FString::FromInt(4))), "");
	}
	else
	{
		return *m_DungeonSizeLevelScale->FindRow<FFloatTable>(FName(*(FString::FromInt(5))), "");
	}
}

const FFloatTable & UDGRG_GameInstance::GetDungeonDiffyScale(E_DIFFICULTY diff) const
{
	E_DIFFICULTY var = diff;

	if ((int)var < (int)E_DIFFICULTY::EASY)
	{
		var = E_DIFFICULTY::EASY;
	}
	if ((int)var > (int)E_DIFFICULTY::LEGEND)
	{
		var = E_DIFFICULTY::LEGEND;
	}

	FName id = m_DifficultyEnumPtr->GetNameByIndex((int)var);

	return *m_DungeonSizeDiffyScale->FindRow<FFloatTable>(id, "");
}
#pragma endregion



void UDGRG_GameInstance::OnMonsterKilled(AMonsterBase *  monsterActor) 
{
	auto MonsterData = monsterActor->GetMonsterData();
	m_ExpManager->IncreaseExp(monsterActor->GetMonsterData().m_EarnExp);
	m_ItemManager->SpawnDropItemFromMonster(monsterActor);
}


void UDGRG_GameInstance::SetPlayerActor(ADGRG_CombatCharacter * combatP)
{
	m_PlayerStatManager->SetPlayerActor(combatP);
}
bool UDGRG_GameInstance::DropItemGround(FVector origin, UStoredItem * item, float radius)
{
	return m_ItemManager->CreateAndDropItemInRandomGround(origin,radius,item);
}



