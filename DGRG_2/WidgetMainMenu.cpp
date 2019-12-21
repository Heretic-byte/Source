// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMainMenu.h"
#include "Components/CanvasPanelSlot.h"
#include "SlateBlueprintLibrary.h"
#include "WidgetBlueprintLibrary.h"
#include "DGRG_PlayerCon.h"
#include "WidgetSlotGrid.h"


void UWidgetMainMenu::InitConstruct()
{
	BindDefaultToggle();
	//
	BindWindowUpdateToggle();
	//
	InitToggle();

	BindToolTipEquipInven();
}

void UWidgetMainMenu::BindWindowUpdateToggle()
{
	m_Status->OnCheckStateChanged.AddDynamic(GetStatMenu(), &UWidgetStatWindow::UpdateOnWindowToggled);
}

void UWidgetMainMenu::BindDefaultToggle()
{
	m_Inven->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptInven);
	m_Status->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptStatus);
	m_Skill->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptSkill);
	m_DungeonInfo->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptDungeonInfo);
	m_Quest->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptQuest);
	m_Shop->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptShop);
	m_Archive->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptArchive);
	m_Option->OnCheckStateChanged.AddDynamic(this, &UWidgetMainMenu::ToggleExecptOption);
}

void UWidgetMainMenu::InitToggle()
{
	m_CurrentSelectToggle = m_Inven;
	m_CurrentSelectWindow = m_EquipInvenParent;
	//
	m_Inven->SetIsChecked(true);

	m_Status->SetIsChecked(false);
	m_Skill->SetIsChecked(false);
	m_DungeonInfo->SetIsChecked(false);
	m_Quest->SetIsChecked(false);
	m_Shop->SetIsChecked(false);
	m_Archive->SetIsChecked(false);
	m_Option->SetIsChecked(false);
	//
	m_EquipInvenParent->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_StatusParent->SetVisibility(ESlateVisibility::Hidden);
	m_SkillParent->SetVisibility(ESlateVisibility::Hidden);
	m_DungeonParent->SetVisibility(ESlateVisibility::Hidden);
	m_QuestParent->SetVisibility(ESlateVisibility::Hidden);
	m_ShopParent->SetVisibility(ESlateVisibility::Hidden);
	m_ArchiveParent->SetVisibility(ESlateVisibility::Hidden);
	m_OptionParent->SetVisibility(ESlateVisibility::Hidden);
	//
	ToggleExecptInven(true);

}
#pragma region Toggles

void UWidgetMainMenu::ToggleExecptInven(bool state)
{
	//if (state) 
	//{
		ToggleWidget(m_Inven, m_EquipInvenParent);

	//}
}

void UWidgetMainMenu::ToggleExecptStatus(bool state)
{
		ToggleWidget(m_Status, m_StatusParent);
}

void UWidgetMainMenu::ToggleExecptSkill(bool state)
{
		ToggleWidget(m_Skill, m_SkillParent);
}

void UWidgetMainMenu::ToggleExecptDungeonInfo(bool state)
{
		ToggleWidget(m_DungeonInfo, m_DungeonParent);
}

void UWidgetMainMenu::ToggleExecptQuest(bool state)
{
		ToggleWidget(m_Quest, m_QuestParent);
}

void UWidgetMainMenu::ToggleExecptShop(bool state)
{
		ToggleWidget(m_Shop, m_ShopParent);
}

void UWidgetMainMenu::ToggleExecptArchive(bool state)
{
		ToggleWidget(m_Archive, m_ArchiveParent);
}

void UWidgetMainMenu::ToggleExecptOption(bool state)
{
		ToggleWidget(m_Option, m_OptionParent);
}
void UWidgetMainMenu::ToggleWidget(UCheckBox * toggleBtn, UPanelWidget * parentWindow)
{
	if (!m_CurrentSelectToggle || !m_CurrentSelectWindow)
	{
		return;
	}

	m_CurrentSelectToggle->SetIsChecked(false);
	m_CurrentSelectWindow->SetVisibility(ESlateVisibility::Hidden);
	m_CurrentSelectToggle = toggleBtn;
	m_CurrentSelectWindow = parentWindow;
	m_CurrentSelectToggle->SetIsChecked(true);
	m_CurrentSelectWindow->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
#pragma endregion

void UWidgetMainMenu::HideAllToolTip()
{
	m_EquipMainToolTip->SetVisibility(ESlateVisibility::Hidden);
	m_EquipSubToolTip->SetVisibility(ESlateVisibility::Hidden);
	m_InvenToolTip->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetMainMenu::OpenInven()
{
	
}

void UWidgetMainMenu::CloseInven()
{
	//HideAllToolTip();
}

void UWidgetMainMenu::ShowEquipToolTip(UStoredItem* item,UWidgetItemVisual* visual)
{
	ShowEquipToolTipRight(m_EquipMainToolTip, visual);
}

void UWidgetMainMenu::ShowInvenToolTip(UStoredItem* item, UWidgetItemVisual* visual)
{
	ShowEquipToolTipLeft(m_InvenToolTip, visual);

	auto* PlayerCharacterP=Cast<APlayerCharacter>(GetOwningPlayer()->GetCharacter());

	auto* EquipSlotP = Cast<UEquipSlot>(visual->GetGridWidget()->GetItemContainer());

	if (item->GetItemData().m_ItemType==E_ITEMTYPE::EQUIP)
	{
		auto* PlayerConP= Cast<ADGRG_PlayerCon>(GetOwningPlayer());

		TArray<UWidgetSlotGrid*> EquipSlotArray;
		EquipSlotArray.Reserve(2);

		PlayerConP->
			GetMasterWidget()->
			GetMainMenu()->
			GetEquipMenu()->
			GetEquipableSlot(Cast<UStoredEquipItem>(item)->GetEquipItemData().m_EquipmentType, EquipSlotArray);

		if (EquipSlotArray.Num() > 0)
		{
			auto* EquipSlotP2 = Cast<UEquipSlot>(EquipSlotArray[0]->GetItemContainer());

			if (EquipSlotP2->GetOccupied())
			{
				ShowEquipToolTipRight(m_EquipMainToolTip, EquipSlotArray[0]->GetVisualArray()[0]);
			}

			//여기서 크고 작고 알려줘야함


			//이게 보조무기 스텟
			
		  /*if (EquipSlotArray.Num() > 1)
			{
				ShowEquipToolTipRight(m_EquipSubToolTip, EquipSlotArray[1]->GetVisualArray()[0]);
			}*/
		}
	}
}

void UWidgetMainMenu::BindToolTipEquipInven()
{
	for(auto* var : GetEquipMenu()->GetWidgetEquipSlots())
	{
		var->SetVisualToolTipClickUpFPtr((UWidgetSlotGrid::FPtrVisualClickUp)&UWidgetMainMenu::ShowEquipToolTip,this);
		var->SetVisualToolTipClickDownFPtr((UWidgetSlotGrid::FPtrVisualClickDown)&UWidgetMainMenu::HideAllToolTip, this);
	}
	GetInvenMenu()->GetInvenGrid()->SetVisualToolTipClickUpFPtr((UWidgetSlotGrid::FPtrVisualClickUp)&UWidgetMainMenu::ShowInvenToolTip, this);
	GetInvenMenu()->GetInvenGrid()->SetVisualToolTipClickDownFPtr((UWidgetSlotGrid::FPtrVisualClickDown)&UWidgetMainMenu::HideAllToolTip, this);

	m_InvenToolTip->m_OnSuccess.BindUObject(this,&UWidgetMainMenu::HideAllToolTip);
	m_EquipMainToolTip->m_OnSuccess.BindUObject(this, &UWidgetMainMenu::HideAllToolTip);
	m_EquipSubToolTip->m_OnSuccess.BindUObject(this, &UWidgetMainMenu::HideAllToolTip);
}

int32 UWidgetMainMenu::NativePaint(const FPaintArgs & Args, const FGeometry & AllottedGeometry,
	const FSlateRect & MyCullingRect, FSlateWindowElementList & OutDrawElements,
	int32 LayerId, const FWidgetStyle & InWidgetStyle, bool bParentEnabled) const
{
	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	BoxDraw2(Context, A, 40.0f, FLinearColor::Red);
	BoxDraw2(Context, B, 40.0f, FLinearColor::Blue);

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

FVector2D UWidgetMainMenu::GetWidgetCenterLocation(UWidget * widget)
{
	FGeometry Geometry = GetCachedGeometry();
	FVector2D Position = Geometry.AbsoluteToLocal(widget->GetCachedGeometry().GetAbsolutePosition())
		+ widget->GetCachedGeometry().GetLocalSize() / 2.0f;
	return Position;
}

FVector2D UWidgetMainMenu::GetWidgetSize(UWidget * widget)
{
	FGeometry Geometry = GetCachedGeometry();
	FVector2D Size =
		Geometry.AbsoluteToLocal(widget->GetCachedGeometry().GetAbsoluteSize());
	return Size;
}

void UWidgetMainMenu::ModifyWidgetY(FVector2D & wantModify,FVector2D& theWidgetSize)
{
	if (wantModify.Y < 0)
	{
		wantModify.Y = 0;
		return;
	}
	auto FullMenuSize = GetCachedGeometry().GetAbsoluteSize();
	float FullY = FullMenuSize.Y;
	float WidgetY = theWidgetSize.Y;
	float theTargetYDown = wantModify.Y + WidgetY;

	if (theTargetYDown > FullY)
	{
		wantModify.Y -= (theTargetYDown-FullY);
		return;
	}
}

void UWidgetMainMenu::ShowEquipToolTipRight(UWidgetItemToolTip* toolTip, UWidgetItemVisual* visual)
{
	toolTip->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	auto ToolTipSize = GetWidgetSize(toolTip);
	auto VisualSize = GetWidgetSize(visual);
	auto VisualPos = GetWidgetCenterLocation(visual);
	auto WantToolTipPos = VisualPos;

	WantToolTipPos.X += (VisualSize.X/2.0f);
	WantToolTipPos.Y-= (ToolTipSize.Y/ 2.0f);

	ModifyWidgetY(WantToolTipPos, ToolTipSize);

	Cast<UCanvasPanelSlot>(toolTip->Slot)->SetPosition(WantToolTipPos);

	toolTip->SetItemToolTip(visual->GetItemInstance());
}

void UWidgetMainMenu::ShowEquipToolTipLeft(UWidgetItemToolTip* toolTip, UWidgetItemVisual* visual)
{
	toolTip->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	auto ToolTipSize = GetWidgetSize(toolTip);
	auto VisualSize = GetWidgetSize(visual);
	auto VisualPos = GetWidgetCenterLocation(visual);
	auto WantToolTipPos = VisualPos;

	WantToolTipPos.X -= (VisualSize.X/2.0f) + ToolTipSize.X;
	WantToolTipPos.Y -= (ToolTipSize.Y/2.0f);

	ModifyWidgetY(WantToolTipPos, ToolTipSize);

	Cast<UCanvasPanelSlot>(toolTip->Slot)->SetPosition(WantToolTipPos);

	toolTip->SetItemToolTip(visual->GetItemInstance());
}

void UWidgetMainMenu::BoxDraw2(FPaintContext& cont,FVector2D point, float widthheight, FLinearColor color) const
{
	float newH = widthheight / 2.0f;

	FVector2D p1 = point;

	p1.X -= newH;
	p1.Y += newH;

	FVector2D p2 = p1;

	p2.X += widthheight;

	UWidgetBlueprintLibrary::DrawLine(cont, p1,p2,color);

	FVector2D p3 = p1;
	FVector2D p4 = p2;

	p3.Y -= widthheight;
	p4.Y -= widthheight;

	UWidgetBlueprintLibrary::DrawLine(cont, p3, p4, color);

	UWidgetBlueprintLibrary::DrawLine(cont, p1, p3, color);

	UWidgetBlueprintLibrary::DrawLine(cont, p2, p4, color);

}

