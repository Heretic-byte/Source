// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetItemVisual.h"
#include "WidgetSlotGrid.h"


#include "SlateBrush.h"
#include "WidgetBlueprintLibrary.h"
#include "DragDropOperationItemVisual.h"


UWidgetItemVisual::UWidgetItemVisual(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)	
{
	m_ItemRef = nullptr;
}


void UWidgetItemVisual::SetItemRef(UStoredItem* item)
{
	m_ItemRef = item;
}

const FBaseItemData & UWidgetItemVisual::GetItemData() const
{
	return m_ItemRef->GetItemData();
}

UStoredItem * UWidgetItemVisual::GetItemInstance() const
{
	return m_ItemRef;
}

void UWidgetItemVisual::SetPivot(FCoord pivt)
{
	m_Pivot = pivt;
}

FCoord UWidgetItemVisual::GetPivot() const
{
	return m_Pivot;
}

void UWidgetItemVisual::SetGridWidget(UWidgetSlotGrid * widget)
{
	m_GridWidget =widget;
}

UWidgetSlotGrid * UWidgetItemVisual::GetGridWidget() const
{
	return m_GridWidget;
}

void UWidgetItemVisual::SetVisualWidget(FCoord pivt, UStoredItem * itemRef, UWidgetSlotGrid * gridWidget)
{
	SetPivot(pivt);
	SetItemRef(itemRef);
	GetItemInstance()->SetItemVisualWidget(this);
	SetGridWidget(gridWidget);
	SetWrapSize(GetItemData().m_WidthHeight);
	FSlateBrush ItemVisualIcon=FSlateBrush();
	ItemVisualIcon.SetImageSize(FVector2D(m_ItemRef->GetItemSize().nX*(int)E_GLOBAL_CONST::SLOTSIZE, m_ItemRef->GetItemSize().nY*(int)E_GLOBAL_CONST::SLOTSIZE));
	ItemVisualIcon.SetResourceObject(GetItemData().m_Icon);
	m_IconImage->SetBrush(ItemVisualIcon);
	m_IconBG->SetColorAndOpacity(GetItemInstance()->GetItemColor());
}

void UWidgetItemVisual::SetWrapSize(FCoord itemSize)
{
	m_MainSizeBox->SetWidthOverride(itemSize.nX*(int)E_GLOBAL_CONST::SLOTSIZE);
	m_MainSizeBox->SetHeightOverride(itemSize.nY*(int)E_GLOBAL_CONST::SLOTSIZE);
}

void UWidgetItemVisual::RemoveItemFromInven()
{
	m_GridWidget->GetItemContainer()->RemoveItemFromPivot(m_Pivot, m_ItemRef);
	m_GridWidget->GetVisualArray().Remove(this);
	RemoveFromParent();
}

UDragDropOperationItemVisual* UWidgetItemVisual::OnDragStart()
{
	auto* DDO= Cast<UDragDropOperationItemVisual>( UWidgetBlueprintLibrary::CreateDragDropOperation(m_ClassDDOItmVisl));
	DDO->SetDragDropItemVisual(m_ItemRef,m_GridWidget,m_Pivot,this);

	RemoveItemFromInven();

	return DDO;
}

FReply UWidgetItemVisual::NativeOnMouseButtonDown(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	FReply Repl= Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
	m_OnItemVisualClickDown.Broadcast();

	return Repl;
}

FReply UWidgetItemVisual::NativeOnMouseButtonUp(const FGeometry & MyGeometry, const FPointerEvent & MouseEvent)
{
	FReply Repl = Super::NativeOnMouseButtonUp(MyGeometry, MouseEvent);

	if (m_OnItemVisualClickUp.IsBound())
	{
		m_OnItemVisualClickUp.Execute(GetItemInstance(), this);
	}

	return Repl;
}
