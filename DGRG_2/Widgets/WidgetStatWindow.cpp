// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetStatWindow.h"
#include "Manager/DGRG_GameInstance.h"
#include "Manager/PlayerStatManager.h"
#include "Manager/ExpManager.h"
#include "Datas/DataTableRowBase.h"
#include "Kismet/KismetTextLibrary.h"
#include "Internationalization.h"


UWidgetStatWindow::UWidgetStatWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_ConstBonusStat = FTextFormat(FText::FromString("+{0}"));

	m_ConstArmor = FTextFormat(FText::FromString("Armor: {0}"));
	m_ConstFArmor = FTextFormat(FText::FromString("FireResist: {0}"));
	m_ConstEArmor = FTextFormat(FText::FromString("ElectricResist: {0}"));
	m_ConstSArmor = FTextFormat(FText::FromString("SoulResist: {0}"));

	m_ConstExpText = FTextFormat(FText::FromString("Exp: {0}/{1}"));
	m_ConstRemainExpText = FTextFormat(FText::FromString("Next Exp: {0}"));//만렙찍으면 0표기

	m_ConstCoreStat = FText::FromString("Core Stat");
	m_ConstResistance = FText::FromString("Resistance");

	m_ConstHealth= FTextFormat(FText::FromString("Hp: {0}/{1}"));
	m_ConstDmg=FTextFormat(FText::FromString("Dmg: {0}"));
	m_ConstASpeed = FTextFormat(FText::FromString("ASpeed: {0}"));
	m_ConstMSpeed = FTextFormat(FText::FromString("MSpeed: {0}"));

	m_ConstItemBonus = FTextFormat(FText::FromString("Item Bonus: {0}"));
	m_ConstExpBonus = FTextFormat(FText::FromString("Exp Bonus: {0}"));
	m_ConstGoldBonus = FTextFormat(FText::FromString("Gold Bonus: {0}"));

	m_ConstRemainStatPoint= FTextFormat(FText::FromString("StatPoint: {0}"));
}

void UWidgetStatWindow::SetGameInstance(UDGRG_GameInstance* gameManager)
{
	m_GameInstance = gameManager;
	m_StatManager = m_GameInstance->GetPlayerStatManager();
	m_ExpManager = m_GameInstance->GetExpManager();
	//업글 바인딩
	SetBinding();
	
}

void UWidgetStatWindow::SetBinding()
{
	m_StrUpgradeButton->OnClicked.AddDynamic(m_StatManager, &UPlayerStatManager::UpgradeStatStr);
	m_AgilUpgradeButton->OnClicked.AddDynamic(m_StatManager, &UPlayerStatManager::UpgradeStatAgil);
	m_LuckUpgradeButton->OnClicked.AddDynamic(m_StatManager, &UPlayerStatManager::UpgradeStatLuck);
	m_StatManager->m_OnStatWindowChanged.AddDynamic(this, &UWidgetStatWindow::UpdateStatWindowAll);

}

void UWidgetStatWindow::UpdateOnWindowToggled(bool isSelected)
{
	if (!isSelected)
	{
		return;
	}

	UpdateStatWindowAll();
}

void UWidgetStatWindow::UpdateStatWindowAll()
{
	SetStrText();
	SetStrBonusText();
	SetAgilText();
	SetAgilBonusText();
	SetLuckText();
	SetLuckBonusText();
	SetArmorText();
	SetFireArmorText();
	SetElecArmorText();
	SetSoulArmorText();
	SetAttackSpeedText();
	SetMoveSpeedText();
	SetExpText();
	SetRemainExpText();
	SetDmgText();
	SetHpText();

	SetConstTextCoreStat();
	SetConstTextResistance();

	SetBonusItemText();
	SetBonusExpText();
	SetBonusGoldText();

	SetRemainStatText();
}

void UWidgetStatWindow::SetStrText()
{
	m_StrDefaultText->SetText(UKismetTextLibrary::Conv_IntToText(m_StatManager->GetFinalCharStat().m_Str.GetDefaultValue()));
}

void UWidgetStatWindow::SetStrBonusText()
{
	float BonusV = m_StatManager->GetFinalCharStat().m_Str.GetOnlyBonusValue();
	if (BonusV <= 0)
	{
		FText NullText;
		m_StrBonusText->SetText(NullText);
		return;
	}
	FFormatOrderedArguments Args;
	Args.Add(BonusV);

	FText FormatText=FText::Format(m_ConstBonusStat, Args);
	m_StrBonusText->SetText(FormatText);
}

void UWidgetStatWindow::SetAgilText()
{
	m_AgilDefaultText->SetText(UKismetTextLibrary::Conv_IntToText(m_StatManager->GetFinalCharStat().m_Agil.GetDefaultValue()));
}

void UWidgetStatWindow::SetAgilBonusText()
{
	float BonusV = m_StatManager->GetFinalCharStat().m_Agil.GetOnlyBonusValue();
	if (BonusV <= 0)
	{
		FText NullText;
		m_AgilBonusText->SetText(NullText);
		return;
	}
	FFormatOrderedArguments Args;
	Args.Add(BonusV);

	FText FormatText = FText::Format(m_ConstBonusStat, Args);
	m_AgilBonusText->SetText(FormatText);
}

void UWidgetStatWindow::SetLuckText()
{
	m_LuckDefaultText->SetText(UKismetTextLibrary::Conv_IntToText(m_StatManager->GetFinalCharStat().m_Luck.GetDefaultValue()));
}

void UWidgetStatWindow::SetLuckBonusText()
{
	float BonusV = m_StatManager->GetFinalCharStat().m_Luck.GetOnlyBonusValue();
	if (BonusV <= 0)
	{
		FText NullText;
		m_LuckBonusText->SetText(NullText);
		return;
	}
	FFormatOrderedArguments Args;
	Args.Add(BonusV);

	FText FormatText = FText::Format(m_ConstBonusStat, Args);
	m_LuckBonusText->SetText(FormatText);
}

void UWidgetStatWindow::SetArmorText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_Armour.m_fFinalValue);
	FText FormatText = FText::Format(m_ConstArmor, Args);
	m_ArmorText->SetText(FormatText);
}

void UWidgetStatWindow::SetFireArmorText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_FireArmour.ToTextPerc(0));
	FText FormatText = FText::Format(m_ConstFArmor, Args);
	m_FireArmorText->SetText(FormatText);
}

void UWidgetStatWindow::SetElecArmorText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_ElectricArmour.ToTextPerc(0));
	FText FormatText = FText::Format(m_ConstEArmor, Args);
	m_ElecArmorText->SetText(FormatText);
}

void UWidgetStatWindow::SetSoulArmorText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_SoulArmour.ToTextPerc(0));
	FText FormatText = FText::Format(m_ConstSArmor, Args);
	m_SoulArmorText->SetText(FormatText);
}

void UWidgetStatWindow::SetAttackSpeedText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_AttackSpeed.ToTextPerc(0));
	FText FormatText = FText::Format(m_ConstASpeed, Args);

	m_ASpeedText->SetText(FormatText);
}

void UWidgetStatWindow::SetMoveSpeedText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_MovementSpeed.ToTextPerc(0));
	FText FormatText = FText::Format(m_ConstMSpeed, Args);

	m_MSpeedText->SetText(FormatText);
}

void UWidgetStatWindow::SetExpText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_ExpManager->GetExp());
	Args.Add(m_ExpManager->GetMaxExp());
	FText FormatText = FText::Format(m_ConstExpText, Args);

	m_ExpText->SetText(FormatText);
}

void UWidgetStatWindow::SetRemainExpText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_ExpManager->GetMaxExp()-m_ExpManager->GetExp());
	FText FormatText = FText::Format(m_ConstRemainExpText, Args);
	m_RemainExpText->SetText(FormatText);
}

void UWidgetStatWindow::SetDmgText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_AttackDamage.ToText());
	FText FormatText = FText::Format(m_ConstDmg, Args);
	m_DmgText->SetText(FormatText);
}

void UWidgetStatWindow::SetHpText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetPlayerChar()->GetCurrentHealth());
	Args.Add(m_StatManager->GetFinalStat().m_HealthPoint.m_fFinalValue);

	FText FormatText = FText::Format(m_ConstHealth, Args);
	m_HpText->SetText(FormatText);
}

void UWidgetStatWindow::SetConstTextCoreStat()
{
	m_ConstTextCoreStat->SetText(m_ConstCoreStat);
}

void UWidgetStatWindow::SetConstTextResistance()
{
	m_ConstTextResistance->SetText(m_ConstResistance);
}

void UWidgetStatWindow::SetBonusItemText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_DropRateScale.ToTextPerc(0));

	FText FormatText = FText::Format(m_ConstItemBonus, Args);
	m_BonusItemText->SetText(FormatText);
}

void UWidgetStatWindow::SetBonusExpText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_ExpScale.ToTextPerc(0));

	FText FormatText = FText::Format(m_ConstExpBonus, Args);
	m_BonusExpText->SetText(FormatText);
}

void UWidgetStatWindow::SetBonusGoldText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetFinalStat().m_GoldBonusScale.ToTextPerc(0));

	FText FormatText = FText::Format(m_ConstGoldBonus, Args);
	m_BonusGoldText->SetText(FormatText);
}

void UWidgetStatWindow::SetRemainStatText()
{
	FFormatOrderedArguments Args;
	Args.Add(m_StatManager->GetRemainStatPoint());
	FText FormatText = FText::Format(m_ConstRemainStatPoint, Args);
	m_RemainStat->SetText(FormatText);
}
