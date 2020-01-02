// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMonsterInfo.h"
#include "Datas/DataTableRowBase.h"
#include "Kismet/KismetTextLibrary.h"
#include "Actor/MonsterBase.h"

UWidgetMonsterInfo::UWidgetMonsterInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_TypePhysical = FText::FromString("Physical");
	m_TypeElectrical = FText::FromString("Electric");
	m_TypeFire = FText::FromString("Fire");
	m_TypeSoul = FText::FromString("Soul");
	m_HealthFormat = FTextFormat(FText::FromString("{0}/{1}"));
	m_CurrentMonster = nullptr;
}

void UWidgetMonsterInfo::SetMonsterInfo(AMonsterBase * monsterRef)
{
	m_CurrentMonster = monsterRef;
	auto& MonData = m_CurrentMonster->GetMonsterData();
	auto& MonStatFinal = m_CurrentMonster->GetStatFinal();

	SetLevel(m_CurrentMonster->GetCurrentLevel());
	SetMonsterName(MonData.m_MonsterName);
	SetMonsterType(m_CurrentMonster->GetCurrentType());
	SetHealthBar(m_CurrentMonster->GetHpPercentOne());
	//»öÁöÁ¤?
	SetHealth(m_CurrentMonster->GetCurrentHealth(),MonStatFinal.m_HealthPoint.m_fFinalValue);
}

void UWidgetMonsterInfo::SetHealthBar_Implementation(float pecent1)
{
	SetHealth(m_CurrentMonster->GetCurrentHealth(), m_CurrentMonster->GetStatFinal().m_HealthPoint.m_fFinalValue);
}

void UWidgetMonsterInfo::SetHealth(float cHealth, float mHealth)
{
	FText maxH = UKismetTextLibrary::Conv_FloatToText(mHealth, ERoundingMode::HalfFromZero);
	FText cH = UKismetTextLibrary::Conv_FloatToText(cHealth, ERoundingMode::HalfFromZero);
	FFormatOrderedArguments Args;
	Args.Add(cHealth);
	Args.Add(mHealth);
	
	m_TextHealth->SetText(FText::Format(m_HealthFormat, Args));
}

void UWidgetMonsterInfo::SetLevel(int level)
{
	auto T =UKismetTextLibrary::Conv_IntToText(level, ERoundingMode::HalfFromZero);
	m_TextLevel->SetText(T);
}

void UWidgetMonsterInfo::SetMonsterName(FText nameT)
{
	m_TextMonsterName->SetText(nameT);
}

void UWidgetMonsterInfo::SetMonsterType(E_ATTACKTYPE type)
{
	FText Twant;
	switch (type)
	{
	case E_ATTACKTYPE::PHYSICAL:
		Twant = m_TypePhysical;
		break;
	case E_ATTACKTYPE::FIRE:
		Twant = m_TypeFire;
		break;
	case E_ATTACKTYPE::ELECTRIC:
		Twant = m_TypeElectrical;
		break;
	case E_ATTACKTYPE::SOUL:
		Twant = m_TypeSoul;
		break;
	}

	m_TextType->SetText(Twant);
}
