// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSlot.h"
#include "Actor/EquipmentShowActor.h"
#include "Actor/DGRG_CombatCharacter.h"
#include "Actor/PortraitRenderActor.h"

UEquipSlot::UEquipSlot()
{
	SetOccupied(false);
	m_EquipItemInstance = nullptr;
	m_CurrentEquipitemActor = nullptr;
	m_AbleEquipSlot.Init(false, (int)E_EQUIPMENT::LEGNTH);
}

bool UEquipSlot::CheckAbleToEquip(UStoredEquipItem * equipItem)
{
	if (!equipItem)
	{
		PRINTF("type NotFOund-EquipSlot");
		return false;
	}

	if (m_IsOccupied)
	{
		PRINTF("Already Occupied");
		return false;
	}

	return CheckEquipSlotWithType(equipItem->GetEquipItemData().m_EquipmentType);
}

bool UEquipSlot::CheckEquipSlotWithType(E_EQUIPMENT typeWant)
{
	if (!m_AbleEquipSlot[(int)typeWant])
	{
		return false;
	}

	return true;
}

void UEquipSlot::SetEquipSlotAble(E_EQUIPMENT typeWant,bool wantAble)
{
	m_AbleEquipSlot[(int)typeWant]= wantAble;
}

void UEquipSlot::SetPortraitActor(APortraitRenderActor * portActor)
{
	m_PortraitActor = portActor;
}

bool UEquipSlot::AddItemToPivot(FCoord pivot,  UStoredItem* dItem)
{
	UStoredEquipItem* EquipItemInstance = Cast<UStoredEquipItem>(dItem);

	if (!CheckAbleToEquip(EquipItemInstance))
	{
		return false;
	}

	if (!Super::AddItemToPivot(pivot, dItem))
	{
		PRINTF("No Space ");
		return false;
	}

	SetEquipItem(EquipItemInstance);
	return true;
}


bool UEquipSlot::AddItemToEmptySpace(UStoredItem * dItem, FCoord & resultPivot)
{

	UStoredEquipItem* EquipItemInstance = Cast<UStoredEquipItem>(dItem);


	if (!CheckAbleToEquip(EquipItemInstance))
	{
		return false;
	}

	if (!Super::AddItemToEmptySpace(dItem, resultPivot))
	{
		PRINTF("No Space ");
		return false;
	}

	SetEquipItem(EquipItemInstance);
	return true;
}
void UEquipSlot::SetEquipItem(UStoredEquipItem * EquipItemInstance)
{
	PRINTF("EquipSlot_EquipCalled");
	SetOccupied(true);
	m_EquipItemInstance = EquipItemInstance;
	m_EquipItemInstance->SetIsEquipped(true);
	m_CurrentEquipItem = m_EquipItemInstance->GetEquipItemData().m_EquipmentType;
	CreateEquipMesh();
	m_OnEquippedItem.Broadcast(m_EquipItemInstance);
	m_OnEquippedBP.Broadcast();
}

bool UEquipSlot::RemoveItemFromPivot(FCoord pivot,  UStoredItem* dItem)
{
	if (!Super::RemoveItemFromPivot(pivot, dItem))
	{
		return false;
	}
	SetUnEquipItem();
	return true;
}

bool UEquipSlot::RemoveItemFromAuto( UStoredItem* dItem)
{
	if (!Super::RemoveItemFromAuto(dItem))
	{
		return false;
	}
	SetUnEquipItem();
	return true;
}

void UEquipSlot::SetUnEquipItem()
{
	PRINTF("EquipSlot_UnEquipCalled");

	m_EquipItemInstance->SetIsEquipped(false);

	m_OnUnequippedItem.Broadcast(m_EquipItemInstance);
	SetOccupied(false);
	m_EquipItemInstance = nullptr;
	m_CurrentEquipItem = E_EQUIPMENT::EMPTY;

	m_OnUnequippedBP.Broadcast();
	if (m_CurrentEquipitemActor)
	{
		m_PortraitActor->DestoryEquipActor(m_CurrentEquipitemActor->GetFName());
		m_CurrentEquipitemActor->Destroy();
	}
}

UStoredEquipItem * UEquipSlot::GetCurrentEquippedData() const
{
	return m_EquipItemInstance;
}

AActor * UEquipSlot::GetCurrentEquipActor()
{
	return m_CurrentEquipitemActor;
}

void UEquipSlot::SetOccupied(bool isOccupied)
{
	m_IsOccupied = isOccupied;
}

FName UEquipSlot::GetSlotSocketName() const
{
	return m_SlotSocketName;
}


void UEquipSlot::SetSlotSocketName(FName nameWant)
{
	m_SlotSocketName = nameWant;
}

E_EQUIPMENT UEquipSlot::GetCurrentEquipType()
{
	return m_CurrentEquipItem;
}

void UEquipSlot::CreateEquipMesh()
{
	auto HasMesh = GetCurrentEquippedData()->GetEquipItemData().m_ItemEquipMesh;
	if (!HasMesh)
	{
		PRINTF("This Item Doesnt Have ShowActor");
		return;
	}

	auto* AttachParent=Cast<ADGRG_CombatCharacter>(GetOwner())->GetMesh();
	auto* CreatedItemActor = GetWorld()->SpawnActor(HasMesh, &AttachParent->GetComponentTransform());
	auto* CreatedItem = Cast<AEquipmentShowActor>(CreatedItemActor);
	FAttachmentTransformRules AttachInfo(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative,false);

	CreatedItem->AttachToComponent(AttachParent, AttachInfo, GetSlotSocketName());
	m_CurrentEquipitemActor = CreatedItem;
	CreatedItem->SetScale(GetCurrentEquippedData()->GetEquipItemData().m_Scale);
	m_PortraitActor->AttachEquipMesh(AttachInfo, GetSlotSocketName(), CreatedItem);
}





