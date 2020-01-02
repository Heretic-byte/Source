// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetItemNameCard.h"
#include "StoredItem.h"
#include "Datas/DataTableRowBase.h"


void UWidgetItemNameCard::SetItemNameText(const FText& itemNameText)
{
	m_ItemName->SetText(itemNameText);
}

void UWidgetItemNameCard::SetItemNameColor(const FColor& colorWant)
{
	m_ItemName->SetColorAndOpacity(FSlateColor(colorWant));
}
