// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetInventoryWindow.h"

void UWidgetInventoryWindow::SetInven(UItemContainer * itemCon)
{
	m_InvenInstance = itemCon;
	m_InventorySlotGrid->SetWidgetSlotGrid(m_InvenInstance);
}
