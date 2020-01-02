// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedItemActor.h"
#include "StoredItem.h"
#include "Datas/DGRG_Struct.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/ItemManager.h"
#include "Datas/DataTableRowBase.h"
#include "DGRG_CombatCharacter.h"

ADroppedItemActor::ADroppedItemActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	m_CurrentItemInstance = nullptr;
	
}


void ADroppedItemActor::IfManualSet()
{
	FBaseItemData* FoundItem = m_ManuallyItemID.GetRow<FBaseItemData>("");
	auto* MyGameInstance = GetGameInstance<UDGRG_GameInstance>();
	auto* ItemInstance = MyGameInstance->GetItemManager()->CreateItemInstance(*FoundItem);
	SetItemData(ItemInstance);
}

void ADroppedItemActor::AddItemToActor(AActor* interMan)
{
	auto InterChar = Cast<ADGRG_CombatCharacter>(interMan);

	if (!InterChar)
	{
		return;
	}
	FCoord NotUse;
	if (InterChar->AddItemToEmptySpace(m_CurrentItemInstance, NotUse))
	{
		Destroy();
	}
}


void ADroppedItemActor::SetItemData(UStoredItem* itemData) 
{
	m_CurrentItemInstance = itemData;
	SetItemMesh(itemData->GetItemData().m_DropStMesh);
	SetWidgetNameCard(itemData);
}


void ADroppedItemActor::SetWidgetNameCard(UStoredItem * itemData)
{
	GetWidgetItemNameCard()->SetItemNameText(itemData->GetItemData().m_Name);
	GetWidgetItemNameCard()->SetItemNameColor(itemData->GetItemColor());
}

