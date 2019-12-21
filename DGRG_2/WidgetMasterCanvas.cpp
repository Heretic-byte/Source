// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMasterCanvas.h"

#include "MonsterBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"
#include "Components/CanvasPanelSlot.h"
#include "WidgetMainMenu.h"



UWidgetMasterCanvas::UWidgetMasterCanvas(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_CanvasPanel = nullptr;
	m_MainMenu = nullptr;

}

void UWidgetMasterCanvas::NativeConstruct()
{
	Super::NativeConstruct();


}

void UWidgetMasterCanvas::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UWidgetMasterCanvas::AddChild(UUserWidget * widget, FVector2D pos, FVector2D alignment)
{
	UCanvasPanelSlot* SlotChildAdd= m_CanvasPanel->AddChildToCanvas(widget);
	SlotChildAdd->SetPosition(pos);
	SlotChildAdd->SetAlignment(alignment);
}

void UWidgetMasterCanvas::ShowMainMenu()
{
	//일시정지 들어가야함
	m_MainMenu->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_MainMenu->OpenInven();
}

void UWidgetMasterCanvas::HideMainMenu()
{
	m_MainMenu->SetVisibility(ESlateVisibility::Hidden);
	m_MainMenu->CloseInven();
}

void UWidgetMasterCanvas::ShowDialWindow()
{
	m_DialogueWindow->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidgetMasterCanvas::HideDialWindow()
{
	m_DialogueWindow->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetMasterCanvas::ShowMonsterInfo()
{
	m_MonsterInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidgetMasterCanvas::HideMonsterInfo()
{
	m_MonsterInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetMasterCanvas::ShowInteractInfo()
{
	m_InteractInfo->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidgetMasterCanvas::HideInteractInfo()
{
	m_InteractInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetMasterCanvas::DeleShowMonsterInfo(AMonsterBase * monster)
{
	ShowMonsterInfo();
}

void UWidgetMasterCanvas::DeleHideMonsterInfo(AMonsterBase * monster)
{
	HideMonsterInfo();
}
