// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDgThemeInfoShower.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/DungeonManager.h"
#include "Datas/DGRG_DungeonThemeAsset.h"


UWidgetDgThemeInfoShower::UWidgetDgThemeInfoShower(const FObjectInitializer& objInit):
Super(objInit)
{
	m_GameInstance = nullptr;
	m_DgManager = nullptr;
}

void UWidgetDgThemeInfoShower::Init()
{
	m_GameInstance = GetGameInstance<UDGRG_GameInstance>();
	m_DgManager = m_GameInstance->GetDungeonManager();
	m_DgManager->m_OnThemeChanged.AddUObject(this, &UWidgetDgThemeInfoShower::ShowThemeInfo);
}

void UWidgetDgThemeInfoShower::ShowThemeInfo(const UDGRG_DungeonThemeAsset * themeAsset)
{
	//themeAsset->GetMonsterClassAry()[0].GetDefaultObject()->GetMonsterData().
	//������ ���ð��� �����ΰ�

	//	�̸�
	//	��
	//	ü
	//	��
	//	�̼�

	//	����� �����
	//	����� �̸�

}

