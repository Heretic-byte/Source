// Fill out your copyright notice in the Description page of Project Settings.


#include "DragDropOperationItemVisual.h"
#include "DGRG_CombatCharacter.h"
#include "WidgetSlotGrid.h"
#include "StoredItem.h"
#include "WidgetItemVisual.h"


bool UDragDropOperationItemVisual::DropItemToGround(ADGRG_CombatCharacter * dropper)
{
	return dropper->DropItemGround(m_ItemRef);
}

void UDragDropOperationItemVisual::SetDragDropItemVisual(UStoredItem * itemRef, UWidgetSlotGrid * preGrid, FCoord prePivot, UWidgetItemVisual* defaultVisual)
{
	m_ItemRef = itemRef;
	m_PreGrid = preGrid;
	m_PreItemVisual = defaultVisual;
	m_PrePivot = prePivot;
	DefaultDragVisual = m_PreItemVisual;
}

void UDragDropOperationItemVisual::BackAddToPreGrid()
{
	m_PreGrid->AddItemToPivot(m_PrePivot, m_ItemRef);
}
void UDragDropOperationItemVisual::RemovePreItemVisualFromInven()
{
	m_PreItemVisual->RemoveItemFromInven();
}