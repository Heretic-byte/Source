// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetEquipWindow.h"
//ctrl kl mark delete

void UWidgetEquipWindow::SetEquipGrid(TArray< UEquipSlot*> equipSlotArray)
{
	m_WidgetSlotArray.Reserve(10);
	m_WidgetSlotArray.Emplace(m_Head);
	m_WidgetSlotArray.Emplace(m_Necklace);
	m_WidgetSlotArray.Emplace(m_Torso);
	m_WidgetSlotArray.Emplace(m_Belt);
	m_WidgetSlotArray.Emplace(m_Glove);
	m_WidgetSlotArray.Emplace(m_Shoe);
	m_WidgetSlotArray.Emplace(m_RightRing);
	m_WidgetSlotArray.Emplace(m_LeftRing);
	m_WidgetSlotArray.Emplace(m_RightWeapon);
	m_WidgetSlotArray.Emplace(m_LeftWeapon);

	for (int i = 0; i < 10; i++)
	{
		m_WidgetSlotArray[i]->SetWidgetSlotGrid(equipSlotArray[i]);
	}
}

void UWidgetEquipWindow::GetEquipableSlot(E_EQUIPMENT equipType, TArray<UWidgetSlotGrid*>& outerArray)
{
	for (int i = 0; i < 10; i++)
	{
		auto* EquipSlotP = Cast<UEquipSlot>(m_WidgetSlotArray[i]->GetItemContainer());
		if ( EquipSlotP->CheckEquipSlotWithType(equipType))
		{
			outerArray.Emplace(m_WidgetSlotArray[i]);
		}
		
	}
}
