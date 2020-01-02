// Fill out your copyright notice in the Description page of Project Settings.


#include "StoredEquipItem.h"
#include "Datas/DGRG_Enum.h"
#include "Datas/DataTableRowBase.h"
#include "Manager/DGRG_GameInstance.h"
#include "Actor/DGRG_PlayerCon.h"
#include "Widgets/WidgetMainMenu.h"
#include "Widgets/WidgetSlotGrid.h"
#include "Manager/OptionManager.h"

UStoredEquipItem::UStoredEquipItem()
{
	m_EquipItemData = nullptr;
	m_ItemQuality = FQuality();
	m_MainItemStat = 0;
	m_IsEquipped = false;
	m_ItemInstanceCache = nullptr;
}

TArray<FOption>& UStoredEquipItem::GetOptionArrays()
{
	return m_Options;
}


const FEquipmentItemData & UStoredEquipItem::GetEquipItemData() const
{
	return *m_EquipItemData;
}

#pragma region ItemOptions

const FItemTier & UStoredEquipItem::GetItemTier() const
{
	return *m_ItemTier;
}

void UStoredEquipItem::SetRandomItemStat(int level)
{
	SetItemLevel(level);
	SetQualityRandom();
	CalculateStat();
}

void UStoredEquipItem::CalculateStat()
{
	float StatCalcu =
		GetEquipItemData().m_EquipmentRatio
		*m_ItemLevel
		*(int)E_GLOBAL_CONST::STATOFFSET
		*GetItemTier().m_ItemRatio;

	 float QualityStat= StatCalcu *m_ItemQuality.m_CurrentQuality;
	 StatCalcu += QualityStat;
	 m_MainItemStat.SetValue(StatCalcu);
	PRINTF("MainStatIs: %f.1", m_MainItemStat.GetFinalValue());
}

void UStoredEquipItem::SetItemLevel(int level)
{
	m_ItemLevel = level;

}

void UStoredEquipItem::SetItemTier(const FItemTier* itemTier)
{
	m_ItemTier = itemTier;
}

void UStoredEquipItem::SetQualityRandom()
{
	m_ItemQuality.SetQualityRandom();
}

#pragma endregion

const FColor& UStoredEquipItem::GetItemColor()
{
	return m_ItemTier->m_SymbolColor;
}

void UStoredEquipItem::SetItemData(const FBaseItemData * baseData)
{
	Super::SetItemData(baseData);
	m_EquipItemData =static_cast<const FEquipmentItemData*>(baseData);
}

bool UStoredEquipItem::UseItem(ADGRG_PlayerCon * playerCon)
{
	Super::UseItem(playerCon);
	if (GetIsEquipped())
	{
		return  TryMoveItemGrid(this->GetItemVisualWidget(),
			playerCon->
			GetMasterWidget()->
			GetMainMenu()->
			GetInvenMenu()->
			GetInvenGrid());
	}
	else
	{

		TArray<UWidgetSlotGrid*> WidgetSlotArray;

		playerCon->
			GetMasterWidget()->
			GetMainMenu()->
			GetEquipMenu()->
			GetEquipableSlot(GetEquipItemData().m_EquipmentType,WidgetSlotArray);

		UEquipSlot* MainHandSlot=Cast<UEquipSlot>(WidgetSlotArray[0]->GetItemContainer());

		if (!MainHandSlot->GetOccupied())
		{
			return TryMoveItemGrid(this->GetItemVisualWidget(),WidgetSlotArray[0]);
		}
		else
		{	
			if (WidgetSlotArray.Num() >1)
			{
				UEquipSlot* SubHandSlot = Cast<UEquipSlot>(WidgetSlotArray[1]->GetItemContainer());
				if (!SubHandSlot->GetOccupied())
				{
					return TryMoveItemGrid(this->GetItemVisualWidget(), WidgetSlotArray[1]);
				}

				if (TrySwapItemGrid(WidgetSlotArray[0]->GetVisualArray()[0], this->GetItemVisualWidget()))
				{
					return true;
				}

				return TrySwapItemGrid(WidgetSlotArray[1]->GetVisualArray()[0], this->GetItemVisualWidget());
			}

			return TrySwapItemGrid(WidgetSlotArray[0]->GetVisualArray()[0], this->GetItemVisualWidget());
		}
	}
	
	return false;
}

bool UStoredEquipItem::GetIsEquipped()
{
	return m_IsEquipped;
}

void UStoredEquipItem::SetIsEquipped(bool equipped)
{
	m_IsEquipped = equipped;
}

bool UStoredEquipItem::TryMoveItemGrid(UWidgetItemVisual * targetItemVisual, UWidgetSlotGrid * targetMoveWantSlot)
{
	if (targetMoveWantSlot->AddItemAuto(targetItemVisual->GetItemInstance()))
	{
		targetItemVisual->RemoveItemFromInven();

		return true;
	}

	return false;
}

bool UStoredEquipItem::TrySwapItemGrid(UWidgetItemVisual * itemFromEquip, UWidgetItemVisual * itemFromInven)
{
	auto* EquipGrid = itemFromEquip->GetGridWidget();
	auto* InvenGrid = itemFromInven->GetGridWidget();

	m_ItemInstanceCache = itemFromInven->GetItemInstance();

	itemFromInven->RemoveItemFromInven();

	if (InvenGrid->AddItemAuto(itemFromEquip->GetItemInstance()))
	{
		itemFromEquip->RemoveItemFromInven();
		EquipGrid->AddItemAuto(m_ItemInstanceCache);
		return true;
	}
	else//인벤에 공간이 없는데?
	{
		InvenGrid->AddItemAuto(m_ItemInstanceCache);
	}

	return false;
}



