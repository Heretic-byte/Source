// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSimpleStatShow.h"
#include "DGRG_Struct.h"


void UWidgetSimpleStatShow::SetStat(FStatDefault& statFinal)
{
	SetDmg(statFinal.m_AttackDamage.ToText());
	SetHp(statFinal.m_HealthPoint.ToText());
	SetArmor(statFinal.m_Armour.ToText());
}