// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetEquipWindow.h"
#include "WidgetItemVisual.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/PortraitRenderActor.h"
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
		equipSlotArray[i]->m_OnEquippedBP.AddDynamic(m_WidgetSlotArray[i],&UWidgetSlotGrid::HideCoverImage);
		equipSlotArray[i]->m_OnUnequippedBP.AddDynamic(m_WidgetSlotArray[i], &UWidgetSlotGrid::ShowCoverImage);
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

void UWidgetEquipWindow::SetSlotImageTwohandedLimit()
{
	FLinearColor ColorW = FLinearColor::Red;
	ColorW.A = 0.9f;
	m_LeftWeapon->SetCoverImageTint(ColorW);
	m_LeftWeapon->SetCoverImage(m_WidgetSlotArray[8]->GetVisualArray()[0]->GetItemData().m_Icon);
}

void UWidgetEquipWindow::SetEquipSlotLimit(E_STANCE stance)
{
	if (stance == E_STANCE::TWOHAND || stance == E_STANCE::KATANA)
	{
		SetSlotImageTwohandedLimit();
		return;
	}
	SetSlotImageDefault();
}

void UWidgetEquipWindow::SetSlotImageDefault()
{
	m_LeftWeapon->SetCoverImageTintDefault();
	m_LeftWeapon->SetCoverImageToDefault();
}
