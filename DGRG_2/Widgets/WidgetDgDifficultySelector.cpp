// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDgDifficultySelector.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/DungeonManager.h"

void UWidgetDgDifficultySelector::Init()
{
	SetDiffyNameTextAry();
	m_GameInstance = GetGameInstance<UDGRG_GameInstance>();
	m_DungeonManager = m_GameInstance->GetDungeonManager();
	m_CurrentDiffy = (int)E_DIFFICULTY::NORMAL;
	m_Min = (int)E_DIFFICULTY::VERYEASY;
	m_Max = (int)E_DIFFICULTY::PILGRIMAGE3;
	m_BtnDecrease->OnClicked.AddDynamic(this,&UWidgetDgDifficultySelector::DecreaseDiffy);
	m_BtnIncrease->OnClicked.AddDynamic(this, &UWidgetDgDifficultySelector::IncreaseDiffy);
	OnDiffyChanaged();
}

void UWidgetDgDifficultySelector::IncreaseDiffy()
{
	if (m_CurrentDiffy >= m_Max)
	{
		return;
	}
	m_CurrentDiffy++;


	OnDiffyChanaged();
}

void UWidgetDgDifficultySelector::DecreaseDiffy()
{
	if (m_CurrentDiffy <= m_Min)
	{
		return;
	}
	m_CurrentDiffy--;


	OnDiffyChanaged();
}

void UWidgetDgDifficultySelector::OnDiffyChanaged_Implementation()
{
	if (m_CurrentDiffy <= m_Min)
	{
		m_BtnDecrease->SetIsEnabled(false);
	}
	else
	{
		m_BtnDecrease->SetIsEnabled(true);
	}
	if (m_CurrentDiffy >= m_Max)
	{
		m_BtnIncrease->SetIsEnabled(false);
	}
	else
	{
		m_BtnIncrease->SetIsEnabled(true);
	}

	m_DungeonManager->SetDifficulty((E_DIFFICULTY)m_CurrentDiffy);
}

const FText& UWidgetDgDifficultySelector::GetDiffyName()const
{
	return m_DiffyNames[m_CurrentDiffy];
}



FText UWidgetDgDifficultySelector::GetDiffyText()
{
	return m_GameInstance->GetDifficultyScale((E_DIFFICULTY)m_CurrentDiffy).ToTextDiffyMonster();
}

void UWidgetDgDifficultySelector::SetDiffyNameTextAry()
{
	for (int i = 0; i < (int)E_DIFFICULTY::LENGTH; i++)
	{
		m_DiffyNames[i]= SetDiffyName(i);
	}
}
FText UWidgetDgDifficultySelector::SetDiffyName(int index)
{
	auto* OptionTypeEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_DIFFICULTY"), true);
	FName id = OptionTypeEnumPtr->GetNameByIndex(index);
	FString ASD = id.ToString();
	ASD.RemoveFromStart("E_DIFFICULTY::");
	FText idT;
	idT = FText::FromString(ASD);

	return idT;
}