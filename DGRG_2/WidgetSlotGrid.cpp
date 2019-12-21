// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSlotGrid.h"
#include "Geometry.h"
#include "Event.h"

#include "Components/GridSlot.h"
#include "WidgetLayoutLibrary.h"
#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "DragDropOperationItemVisual.h"
#include "Kismet/KismetMathLibrary.h"

void UWidgetSlotGrid::SetWidgetSlotGrid(UItemContainer * itemCon)
{
	m_ItemContainer = itemCon;
	BindEventToItemContainer();
	ClearGrid();
	SetGrid(m_ItemContainer->GetInvenSize());
	m_WidgetItemVisualArray.Reserve(20);
}

void UWidgetSlotGrid::SetGrid(FCoord invenSize)
{
	int InvenX = invenSize.nX;
	int InvenY = invenSize.nY;

	for(int x=0; x<InvenX;x++)
	{
		for (int y = 0; y < InvenY; y++)
		{
			m_SlotGridPanel->SetColumnFill(x, 1);
			m_SlotGridPanel->SetRowFill(y, 1);
			UWidgetSlot* _Slot= CreateWidget<UWidgetSlot>(this,m_ClassWidgetSlot);
			UGridSlot* _ChildSlot= m_SlotGridPanel->AddChildToGrid(_Slot);
			_ChildSlot->SetColumn(x);
			_ChildSlot->SetRow(y);
		}
	}
	SetBoxSize(invenSize);
}

UWidgetSlot* UWidgetSlotGrid::GetChildAtCoord(FCoord pivot)
{
	int index = (m_ItemContainer->GetInvenSize().nY*pivot.nX) + pivot.nY;
	auto* WidgetSlot= m_SlotGridPanel->GetChildAt(index);
	auto* WidgetGridSlot= UWidgetLayoutLibrary::SlotAsGridSlot(WidgetSlot);

	WidgetGridSlot->SetColumnSpan(0);
	WidgetGridSlot->SetRowSpan(0);

	return Cast<UWidgetSlot>(WidgetSlot);
}

FCoord UWidgetSlotGrid::MouseToInvenIndex(FVector2D mouseCoord)
{
	int X = UKismetMathLibrary::Round(mouseCoord.X / (int)E_GLOBAL_CONST::SLOTSIZE);
	int Y = UKismetMathLibrary::FCeil(mouseCoord.Y / (int)E_GLOBAL_CONST::SLOTSIZE);
	FCoord NewCoord = FCoord(X, Y);
	return NewCoord;
}

FCoord UWidgetSlotGrid::GetTargetPivot(FCoord mouseCenter, UStoredItem * itemRef)
{
	float PivotX;
	float PivotY;
	float ItemWidthX= itemRef->GetItemSize().nX;
	float ItemHeightY = itemRef->GetItemSize().nY;
	FCoord MouseCenter =mouseCenter;
	FCoord Result;

	PivotX = MouseCenter.nX - (ItemWidthX / 2);
	PivotY = MouseCenter.nY - (ItemHeightY / 2);
	//
	if (MouseCenter.nX <= 0)
	{
		PivotX = 0;

		if (MouseCenter.nY <= 0)
		{
			PivotY = 0;

			return Result = FCoord(PivotX, PivotY);
		}

		int YLastIndex = m_ItemContainer->GetInvenSize().nY - 1;

		if (MouseCenter.nY <= YLastIndex)
		{
			PivotY = MouseCenter.nY - ItemHeightY + 1;

			return Result = FCoord(PivotX, PivotY);
		}

		PivotY = MouseCenter.nY - (ItemHeightY / 2);

		return Result = FCoord(PivotX, PivotY);
	}

	int XLastIndex = m_ItemContainer->GetInvenSize().nX - 1;

	if (MouseCenter.nX <= XLastIndex)
	{
		PivotX = MouseCenter.nX - ItemWidthX + 1;

		if (MouseCenter.nY <= 0)
		{
			PivotY = 0;

			return Result = FCoord(PivotX, PivotY);
		}

		int YLastIndex = m_ItemContainer->GetInvenSize().nY - 1;

		if (MouseCenter.nY <= YLastIndex)
		{
			PivotY = MouseCenter.nY - ItemHeightY + 1;

			return Result = FCoord(PivotX, PivotY);
		}

		PivotY = MouseCenter.nY - (ItemHeightY / 2);

		return Result = FCoord(PivotX, PivotY);
	}


	PivotX = MouseCenter.nX - (ItemWidthX / 2);

	if (MouseCenter.nY <= 0)
	{
		PivotY = 0;

		return Result = FCoord(PivotX, PivotY);
	}

	int YLastIndex = m_ItemContainer->GetInvenSize().nY - 1;

	if (MouseCenter.nY <= YLastIndex)
	{
		PivotY = MouseCenter.nY - ItemHeightY + 1;

		return Result = FCoord(PivotX, PivotY);
	}

	PivotY = MouseCenter.nY - (ItemHeightY / 2);

	return Result = FCoord(PivotX, PivotY);
}

void UWidgetSlotGrid::AddItemVisualToSlot(UWidgetItemVisual * itemVisual, FCoord pivot)
{
	GetChildAtCoord(pivot)->AddItemVisual(itemVisual);
	m_WidgetItemVisualArray.Emplace(itemVisual);
}

void UWidgetSlotGrid::CreateAddItemVisualWidget(UStoredItem * itemRef, FCoord pivot)
{
	UWidgetItemVisual* ItemVisual = CreateWidget<UWidgetItemVisual>(GetOwningPlayer(), m_ClassWidgetItemVisual);
	ItemVisual->SetVisualWidget(pivot, itemRef, this);
	AddItemVisualToSlot(ItemVisual, pivot);

	if(m_FPtrClickUpGiver)
		ItemVisual->m_OnItemVisualClickUp.BindUObject(m_FPtrClickUpGiver, m_FPtrItemVisualToolTipClickUp);
	if (m_FPtrClickDownGiver)
		ItemVisual->m_OnItemVisualClickDown.AddUObject(m_FPtrClickDownGiver, m_FPtrItemVisualToolTipClickDown);
}

void UWidgetSlotGrid::ClearGrid()
{
	m_SlotGridPanel->ClearChildren();
}

void UWidgetSlotGrid::SetBoxSize(FCoord invenSize)
{
	float Width= invenSize.nX*(int)E_GLOBAL_CONST::SLOTSIZE;
	float Height= invenSize.nY*(int)E_GLOBAL_CONST::SLOTSIZE;

	m_DropSizeBox->SetWidthOverride(Width);
	m_DropSizeBox->SetHeightOverride(Height);
}


bool UWidgetSlotGrid::OnDropOnSlot(FGeometry geo, FPointerEvent pEvent, UDragDropOperation * ddo)
{
	auto* DDO= Cast<UDragDropOperationItemVisual>(ddo);

	UStoredItem* ItemRef = DDO->GetItemRef();

	const FVector2D& ScreepPosition = pEvent.GetScreenSpacePosition();

	FVector2D AbsLocalPos = geo.AbsoluteToLocal(ScreepPosition);

	FCoord InvenIndex = MouseToInvenIndex(AbsLocalPos);

	FCoord TargetPivot=GetTargetPivot(InvenIndex, ItemRef);


	bool Result= AddItemToPivot(TargetPivot, DDO->GetItemRef());

	if (Result)
	{
		PRINTF("True");
	}
	else
	{
		PRINTF("False");
		DDO->BackAddToPreGrid();
	}

	return Result;
}

void UWidgetSlotGrid::SetVisualToolTipClickUpFPtr(FPtrVisualClickUp fptr, UObject * giver)
{
	m_FPtrItemVisualToolTipClickUp = fptr;
	m_FPtrClickUpGiver = giver;
}

void UWidgetSlotGrid::SetVisualToolTipClickDownFPtr(FPtrVisualClickDown fptr, UObject * giver)
{
	m_FPtrItemVisualToolTipClickDown = fptr;
	m_FPtrClickDownGiver = giver;
}

 TArray<UWidgetItemVisual*>& UWidgetSlotGrid::GetVisualArray()
{
	return m_WidgetItemVisualArray;
}

void UWidgetSlotGrid::BindEventToItemContainer()
{
	m_ItemContainer->OnItemAdd.AddUObject(this, &UWidgetSlotGrid::CreateAddItemVisualWidget);
}

bool UWidgetSlotGrid::AddItemToPivot(FCoord pivot, UStoredItem * itemRef)
{
	 return m_ItemContainer->AddItemToPivot(pivot,itemRef);
}

bool UWidgetSlotGrid::AddItemAuto(UStoredItem * itemRef)
{
	FCoord NotUse;
	return m_ItemContainer->AddItemToEmptySpace(itemRef, NotUse);
}

void UWidgetSlotGrid::UpdateGrid(UItemContainer * newItemCon)
{
	//아이템의 목록이 이미 있어야함
}

