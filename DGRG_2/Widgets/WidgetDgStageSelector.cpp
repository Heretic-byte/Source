// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDgStageSelector.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/DungeonManager.h"
#include "Datas/DGRG_Enum.h"
#include "Actor/PlayerCharacter.h"
#include "Widgets/WidgetMasterCanvas.h"

UWidgetDgStageSelector::UWidgetDgStageSelector(const FObjectInitializer& objInit)
	:Super(objInit)
{
	m_CurrentStage = 1;
	m_GameInstance = nullptr;
	m_DungeonManager = nullptr;
	m_PlayerActor = nullptr;
}

void UWidgetDgStageSelector::Init()
{
	m_GameInstance=GetGameInstance<UDGRG_GameInstance>();
	m_DungeonManager = m_GameInstance->GetDungeonManager();
	m_DungeonManager->m_OnDgBuildComplete.AddDynamic(this,&UWidgetDgStageSelector::OnDungeonBuildComplete);
	m_DungeonManager->m_OnThemeChanged.AddUObject(this, &UWidgetDgStageSelector::OnThemeChanged);
	m_PlayerActor = m_GameInstance->GetPlayerCharacter();
	m_BtnDecrease->OnClicked.AddDynamic(this, &UWidgetDgStageSelector::DecreaseStageLevel);
	m_BtnIncrease->OnClicked.AddDynamic(this, &UWidgetDgStageSelector::IncreaseStageLevel);
	OnStageChanged();
	SetStageMobTheme(0);
}


void UWidgetDgStageSelector::IncreaseStageLevel()
{
	if (m_CurrentStage >= (int)E_GLOBAL_CONST::MAXSTAGE)
	{
		return;
	}
	m_CurrentStage++;
	OnStageChanged();
}

void UWidgetDgStageSelector::DecreaseStageLevel()
{
	if (m_CurrentStage <= 1)
	{
		return;
	}
	m_CurrentStage--;
	OnStageChanged();
}

void UWidgetDgStageSelector::EnterTheDungeon()
{
	int MobLevel=CalculateStageToMobLevel();
	SetStageMobTheme(MobLevel);
	m_DungeonManager->SetDungeonLevel(MobLevel);
	m_DungeonManager->GenerateDungeon();
}

void UWidgetDgStageSelector::OnDungeonBuildComplete()
{
	FVector Point = m_GameInstance->GetDungeonManager()->GetStartPoint();
	Point.Z += 100.f;
	FRotator Rot(0, 0, 0);

	//텔레포트 안되는거 대비해야함
	m_PlayerActor->TeleportTo(Point, Rot);
	m_DungeonManager->ShowFog();
	m_GameInstance->GetMasterCanvas()->HideDgEnter();
}

void UWidgetDgStageSelector::OnStageChanged_Implementation()
{
	if (m_CurrentStage <= 1)
	{
		m_BtnDecrease->SetIsEnabled(false);
	}
	else
	{
		m_BtnDecrease->SetIsEnabled(true);
	}
	if (m_CurrentStage >= (int)E_GLOBAL_CONST::MAXSTAGE)
	{
		m_BtnIncrease->SetIsEnabled(false);
	}
	else
	{
		m_BtnIncrease->SetIsEnabled(true);
	}
}

int UWidgetDgStageSelector::CalculateStageToMobLevel()
{
	int Result= FMath::CeilToInt(m_CurrentStage / 20.f);
	//Result += 1;
	return Result;
}

void UWidgetDgStageSelector::SetStageMobTheme(int resultStage)
{
	//resultStage
	//1~5, 6~10, 11~15, 16~20
	//21~25, 26~30, 31~35, 36~40
	//좀비, 해골, 악마, 혼종
	//50번 뺑뺑이
	//나오는 몹에도 차이가 생겨야할테니
	//결국 테이블 필요할것
	m_DungeonManager->SetDungeonTheme(0);
}
