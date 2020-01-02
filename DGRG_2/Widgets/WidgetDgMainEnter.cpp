// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDgMainEnter.h"
#include "Manager/DGRG_GameInstance.h"
#include "Widgets/WidgetMasterCanvas.h"
#include "WidgetDgStageSelector.h"
#include "WidgetDgDifficultySelector.h"
#include "WidgetDgThemeInfoShower.h"

void UWidgetDgMainEnter::Init()
{
	m_StageSelector->Init();
	m_DiffySelector->Init();
	m_ThemeSelector->Init();
}

UWidgetDgStageSelector * UWidgetDgMainEnter::GetStageSelector()
{
	return m_StageSelector;
}

void UWidgetDgMainEnter::CloseDgEnterWidget()
{
	GetGameInstance<UDGRG_GameInstance>()->GetMasterCanvas()->HideDgEnter();
}
