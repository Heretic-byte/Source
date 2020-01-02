// Fill out your copyright notice in the Description page of Project Settings.


#include "StoredItem.h"
#include "Manager/DGRG_GameInstance.h"
#include "Datas/DataTableRowBase.h"
#include "Actor/DGRG_PlayerCon.h"

UStoredItem::UStoredItem():
	m_WidthHeight(2,3)

{
	m_CurrentStackCount = 1;
	m_ItemData = nullptr;
	m_BaseWhiteColor= FColor::White;
}

 const FBaseItemData & UStoredItem::GetItemData() const
{
	return *m_ItemData;
}

void UStoredItem::SetItemData(const FBaseItemData * baseData) 
{
	m_ItemData = baseData;
	m_WidthHeight = m_ItemData->m_WidthHeight;
}

int UStoredItem::GetCurrentStack()
{
	return m_CurrentStackCount;
}


const FColor&  UStoredItem::GetItemColor()
{
	return m_BaseWhiteColor;
}

bool UStoredItem::UseItem(ADGRG_PlayerCon * playerCon)
{
	PRINTF("BaseItemUse");

	return false;
}

FCoord & UStoredItem::GetItemSize()
{
	return m_WidthHeight;
}

void UStoredItem::SetItemVisualWidget(UWidgetItemVisual * visualWidget)
{
	m_MyWidgetVisual = visualWidget;
}

UWidgetItemVisual * UStoredItem::GetItemVisualWidget()
{
	return m_MyWidgetVisual;
}

