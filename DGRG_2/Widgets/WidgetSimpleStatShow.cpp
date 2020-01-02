// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSimpleStatShow.h"
#include "Datas/DGRG_Struct.h"


void UWidgetSimpleStatShow::SetStat(FStatDefault& statFinal)
{
	SetDmg(statFinal.m_AttackDamage.ToText(0));
	SetHp(statFinal.m_HealthPoint.ToText(0));
	SetArmor(statFinal.m_Armour.ToText(0));
}