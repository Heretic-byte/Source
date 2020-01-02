// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSlot.h"
#include "WidgetItemVisual.h"


void UWidgetSlot::AddItemVisual(UWidgetItemVisual* itemVisual)
{
	m_SlotGridPanel->AddChild(itemVisual);
}
