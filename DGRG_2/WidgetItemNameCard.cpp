// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetItemNameCard.h"
#include "StoredItem.h"

void UWidgetItemNameCard::SetItemName(UStoredItem * itemRef)
{
	m_ItemName->SetColorAndOpacity(FSlateColor(itemRef->GetItemColor()));
	m_ItemName->SetText(itemRef->GetItemData().m_Name);
}
