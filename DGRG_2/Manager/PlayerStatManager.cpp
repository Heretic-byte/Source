// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatManager.h"
#include "DGRG_GameInstance.h"
#include "Actor/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OptionManager.h"
//#include "DGRG_2GameMode.h"


UPlayerStatManager::UPlayerStatManager()
{
	
}
UPlayerStatManager::UPlayerStatManager(const FObjectInitializer& ObjectInitializer)
{
	m_LevelUpPerStatGain = 3;
	m_CurrentAvailableStats = 0;
	SetFuncPtr();
}

void UPlayerStatManager::Init(UDGRG_GameInstance * gameInstance)
{
	Super::Init(gameInstance);
}

void UPlayerStatManager::SetFuncPtr()
{
	m_EquipFuncPtr[(int)E_EQUIPMENT::HEAD] = &UPlayerStatManager::IncreaseAbsArmor;
	m_EquipFuncPtr[(int)E_EQUIPMENT::TORSO] = &UPlayerStatManager::IncreaseAbsArmor;
	m_EquipFuncPtr[(int)E_EQUIPMENT::BELT] = &UPlayerStatManager::IncreaseAbsArmor;
	m_EquipFuncPtr[(int)E_EQUIPMENT::SHOE] = &UPlayerStatManager::IncreaseAbsArmor;
	m_EquipFuncPtr[(int)E_EQUIPMENT::GLOVE] = &UPlayerStatManager::IncreaseAbsArmor;
	m_EquipFuncPtr[(int)E_EQUIPMENT::SHIELD] = &UPlayerStatManager::IncreaseAbsArmor;

	m_EquipFuncPtr[(int)E_EQUIPMENT::BELT] = &UPlayerStatManager::IncreaseAbsHp;
	m_EquipFuncPtr[(int)E_EQUIPMENT::NECK] = &UPlayerStatManager::IncreaseAbsHp;
	m_EquipFuncPtr[(int)E_EQUIPMENT::RING] = &UPlayerStatManager::IncreaseAbsHp;

	m_EquipFuncPtr[(int)E_EQUIPMENT::ONEHAND] = &UPlayerStatManager::IncreaseAbsDamage;
	m_EquipFuncPtr[(int)E_EQUIPMENT::TWOHAND] = &UPlayerStatManager::IncreaseAbsDamage;
	m_EquipFuncPtr[(int)E_EQUIPMENT::DAGGER] = &UPlayerStatManager::IncreaseAbsDamage;
	m_EquipFuncPtr[(int)E_EQUIPMENT::KATANA] = &UPlayerStatManager::IncreaseAbsDamage;

	m_UnequipFuncPtr[(int)E_EQUIPMENT::HEAD] = &UPlayerStatManager::DecreaseAbsArmor;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::TORSO] = &UPlayerStatManager::DecreaseAbsArmor;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::BELT] = &UPlayerStatManager::DecreaseAbsArmor;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::SHOE] = &UPlayerStatManager::DecreaseAbsArmor;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::GLOVE] = &UPlayerStatManager::DecreaseAbsArmor;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::SHIELD] = &UPlayerStatManager::DecreaseAbsArmor;

	m_UnequipFuncPtr[(int)E_EQUIPMENT::BELT] = &UPlayerStatManager::DecreaseAbsHp;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::NECK] = &UPlayerStatManager::DecreaseAbsHp;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::RING] = &UPlayerStatManager::DecreaseAbsHp;

	m_UnequipFuncPtr[(int)E_EQUIPMENT::ONEHAND] = &UPlayerStatManager::DecreaseAbsDamage;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::TWOHAND] = &UPlayerStatManager::DecreaseAbsDamage;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::DAGGER] = &UPlayerStatManager::DecreaseAbsDamage;
	m_UnequipFuncPtr[(int)E_EQUIPMENT::KATANA] = &UPlayerStatManager::DecreaseAbsDamage;
}

void UPlayerStatManager::SetPlayerActor(ADGRG_CombatCharacter * actorP)
{
	m_PlayerActor = actorP;
	m_ValueStatFinal = m_PlayerActor->GetStatFinalPtr();
	auto& HumanStat = m_GameInstance->GetHumanStat(m_PlayerActor->GetCharID().RowName);
	m_ValueStatFinal->SetStatFromDefault(HumanStat.m_StatDefault);
	m_ValueStatFinal->m_AttackSpeed.SetMaxLimit(3.f);
	m_ValueStatFinal->m_MovementSpeed.SetMaxLimit(500.f);
	m_CharStatFinal.SetStatFromDefault(HumanStat.m_StatChar);

	SetCharStatToValue();

	for (auto& Slot : actorP->GetEquipSlotArray())
	{
		Slot->m_OnEquippedItem.AddDynamic(this,&UPlayerStatManager::ModifyEquipItem);
		Slot->m_OnUnequippedItem.AddDynamic(this, &UPlayerStatManager::ModifyUnequipItem);
	}

	UpdateWidget();
}

void UPlayerStatManager::GainStatLevelUp()
{
	GainStatPoint(m_LevelUpPerStatGain);
}

void UPlayerStatManager::GainStatPoint(int amount)
{
	m_CurrentAvailableStats += amount;
}


void UPlayerStatManager::UpgradeStatStr()
{
	if (m_CurrentAvailableStats <= 0)
	{
		return;
	}
	m_CurrentAvailableStats--;

	IncreaseDefaultCharStat_Str(1);

	UpdateWidget();
}

void UPlayerStatManager::UpgradeStatAgil()
{
	if (m_CurrentAvailableStats <= 0)
	{
		return;
	}
	m_CurrentAvailableStats--;

	IncreaseDefaultCharStat_Agil(1);

	UpdateWidget();
}

void UPlayerStatManager::UpgradeStatLuck()
{
	if (m_CurrentAvailableStats <= 0)
	{
		return;
	}
	m_CurrentAvailableStats--;

	IncreaseDefaultCharStat_Luck(1);

	UpdateWidget();
}

void UPlayerStatManager::ModifyEquipItem(UStoredEquipItem * equipItem)
{
	float MainStat = equipItem->GetMainStat().GetFinalValue();
	const FEquipmentItemData& Item=(equipItem->GetEquipItemData());
	PerformEquipFuncPtr(Item.m_EquipmentType, MainStat);
	m_GameInstance->GetOptionManager()->EquipOptions(equipItem->GetOptionArrays());

	UpdateWidget();
}


void UPlayerStatManager::ModifyUnequipItem(UStoredEquipItem * equipItem)
{
	float MainStat = equipItem->GetMainStat().GetFinalValue();
	const FEquipmentItemData& Item = (equipItem->GetEquipItemData());
	PerformUnequipFuncPtr(Item.m_EquipmentType, MainStat);
	m_GameInstance->GetOptionManager()->UnequipOptions(equipItem->GetOptionArrays());

	UpdateWidget();
}

void UPlayerStatManager::UpdateWidget()
{
	m_OnFinalStatUpdated.ExecuteIfBound(*m_ValueStatFinal);
	m_OnStatWindowChanged.Broadcast();
}

void UPlayerStatManager::IncreaseAbsDamage(float dmg)
{
	m_ValueStatFinal->m_AttackDamage.IncreaseAbsBonus(dmg);
}

void UPlayerStatManager::IncreaseAbsArmor(float armor)
{
	m_ValueStatFinal->m_Armour.IncreaseAbsBonus(armor);
}

void UPlayerStatManager::IncreaseAbsHp(float hp)
{
	m_ValueStatFinal->m_HealthPoint.IncreaseAbsBonus(hp);
}

void UPlayerStatManager::IncreasePerDamage(float dmg)
{
	m_ValueStatFinal->m_AttackDamage.IncreasePerBonus(dmg);
}

void UPlayerStatManager::IncreasePerArmor(float armor)
{
	m_ValueStatFinal->m_Armour.IncreasePerBonus(armor);
}

void UPlayerStatManager::IncreasePerHp(float hp)
{
	m_ValueStatFinal->m_HealthPoint.IncreasePerBonus(hp);
}

void UPlayerStatManager::DecreaseAbsDamage(float dmg)
{
	m_ValueStatFinal->m_AttackDamage.DecreaseAbsBonus(dmg);
}

void UPlayerStatManager::DecreaseAbsArmor(float armor)
{
	m_ValueStatFinal->m_Armour.DecreaseAbsBonus(armor);
}

void UPlayerStatManager::DecreaseAbsHp(float hp)
{
	m_ValueStatFinal->m_HealthPoint.DecreaseAbsBonus(hp);
}

void UPlayerStatManager::DecreasePerDamage(float dmg)
{
	m_ValueStatFinal->m_AttackDamage.DecreasePerBonus(dmg);
}

void UPlayerStatManager::DecreasePerArmor(float armor)
{
	m_ValueStatFinal->m_Armour.DecreasePerBonus(armor);
}

void UPlayerStatManager::DecreasePerHp(float hp)
{
	m_ValueStatFinal->m_HealthPoint.DecreasePerBonus(hp);
}

void UPlayerStatManager::IncreaseAbsAttackSpeed(float v)
{
	m_ValueStatFinal->m_AttackSpeed.IncreaseAbsBonus(v);
}

void UPlayerStatManager::IncreasePerAttackSpeed(float v)
{
	m_ValueStatFinal->m_AttackSpeed.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreaseAbsMoveSpeed(float v)
{
	m_ValueStatFinal->m_MovementSpeed.IncreaseAbsBonus(v);
}

void UPlayerStatManager::IncreasePerMoveSpeed(float v)
{
	m_ValueStatFinal->m_MovementSpeed.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreaseAbsFireArmor(float v)
{
	m_ValueStatFinal->m_FireArmour.IncreaseAbsBonus(v);
}

void UPlayerStatManager::IncreasePerFireArmor(float v)
{
	m_ValueStatFinal->m_FireArmour.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreaseAbsElecArmor(float v)
{
	m_ValueStatFinal->m_ElectricArmour.IncreaseAbsBonus(v);
}

void UPlayerStatManager::IncreasePerElecArmor(float v)
{
	m_ValueStatFinal->m_ElectricArmour.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreaseAbsSoulArmor(float v)
{
	m_ValueStatFinal->m_SoulArmour.IncreaseAbsBonus(v);
}

void UPlayerStatManager::IncreasePerSoulArmor(float v)
{
	m_ValueStatFinal->m_ElectricArmour.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreasePerExpScale(float v)
{
	m_ValueStatFinal->m_ExpScale.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreasePerDropRate(float v)
{
	m_ValueStatFinal->m_DropRateScale.IncreasePerBonus(v);
}

void UPlayerStatManager::IncreasePerGoldScale(float v)
{
	m_ValueStatFinal->m_GoldBonusScale.IncreasePerBonus(v);
}

void UPlayerStatManager::DecreaseAbsAttackSpeed(float v)
{
	m_ValueStatFinal->m_AttackSpeed.DecreaseAbsBonus(v);
}

void UPlayerStatManager::DecreasePerAttackSpeed(float v)
{
	m_ValueStatFinal->m_AttackSpeed.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreaseAbsMoveSpeed(float v)
{
	m_ValueStatFinal->m_MovementSpeed.DecreaseAbsBonus(v);
}

void UPlayerStatManager::DecreasePerMoveSpeed(float v)
{
	m_ValueStatFinal->m_MovementSpeed.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreaseAbsFireArmor(float v)
{
	m_ValueStatFinal->m_FireArmour.DecreaseAbsBonus(v);
}

void UPlayerStatManager::DecreasePerFireArmor(float v)
{
	m_ValueStatFinal->m_FireArmour.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreaseAbsElecArmor(float v)
{
	m_ValueStatFinal->m_ElectricArmour.DecreaseAbsBonus(v);
}

void UPlayerStatManager::DecreasePerElecArmor(float v)
{
	m_ValueStatFinal->m_ElectricArmour.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreaseAbsSoulArmor(float v)
{
	m_ValueStatFinal->m_SoulArmour.DecreaseAbsBonus(v);
}

void UPlayerStatManager::DecreasePerSoulArmor(float v)
{
	m_ValueStatFinal->m_SoulArmour.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreasePerExpScale(float v)
{
	m_ValueStatFinal->m_ExpScale.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreasePerDropRate(float v)
{
	m_ValueStatFinal->m_DropRateScale.DecreasePerBonus(v);
}

void UPlayerStatManager::DecreasePerGoldScale(float v)
{
	m_ValueStatFinal->m_GoldBonusScale.DecreasePerBonus(v);
}
//
void UPlayerStatManager::IncreaseDefaultCharStat_Str(int v)
{
	m_CharStatFinal.m_Str.IncreaseDefaultValue(v);
	ApplyCharStat_Str(v);
}

void UPlayerStatManager::IncreaseDefaultCharStat_Agil(int v)
{
	m_CharStatFinal.m_Agil.IncreaseDefaultValue(v);
	ApplyCharStat_Agil(v);
}

void UPlayerStatManager::IncreaseDefaultCharStat_Luck(int v)
{
	m_CharStatFinal.m_Luck.IncreaseDefaultValue(v);
	ApplyCharStat_Luck(v);
}

void UPlayerStatManager::DecreaseDefaultCharStat_Str(int v)
{
	m_CharStatFinal.m_Str.DecreaseDefaultValue(v);
	CancelCharStat_Str(v);
}

void UPlayerStatManager::DecreaseDefaultCharStat_Agil(int v)
{
	m_CharStatFinal.m_Agil.DecreaseDefaultValue(v);
	CancelCharStat_Agil(v);
}

void UPlayerStatManager::DecreaseDefaultCharStat_Luck(int v)
{
	m_CharStatFinal.m_Luck.DecreaseAbsBonus(v);
	CancelCharStat_Luck(v);
}

void UPlayerStatManager::IncreaseBonusCharStat_Str(int v)
{
	m_CharStatFinal.m_Str.IncreaseAbsBonus(v);
	ApplyCharStat_Str(v);
}

void UPlayerStatManager::IncreaseBonusCharStat_Agil(int v)
{
	m_CharStatFinal.m_Agil.IncreaseAbsBonus(v);
	ApplyCharStat_Agil(v);
}

void UPlayerStatManager::IncreaseBonusCharStat_Luck(int v)
{
	m_CharStatFinal.m_Luck.IncreaseAbsBonus(v);
	ApplyCharStat_Luck(v);
}

void UPlayerStatManager::DecreaseBonusCharStat_Str(int v)
{
	m_CharStatFinal.m_Str.DecreaseAbsBonus(v);
	CancelCharStat_Str(v);
}

void UPlayerStatManager::DecreaseBonusCharStat_Agil(int v)
{
	m_CharStatFinal.m_Agil.DecreaseAbsBonus(v);
	CancelCharStat_Agil(v);
}

void UPlayerStatManager::DecreaseBonusCharStat_Luck(int v)
{
	m_CharStatFinal.m_Luck.DecreaseAbsBonus(v);
	m_ValueStatFinal->m_SoulArmour.DecreaseAbsBonus(2.f*v);
}


void UPlayerStatManager::ApplyCharStat_Str(int v)
{
	m_ValueStatFinal->m_HealthPoint.IncreaseAbsBonus(2.4f*v);
	m_ValueStatFinal->m_AttackDamage.IncreaseAbsBonus(1.f*v);
	m_ValueStatFinal->m_FireArmour.IncreaseAbsBonus(5.f*v);
	m_PlayerActor->OnHealthChangeBroadcast();
}
void UPlayerStatManager::ApplyCharStat_Agil(int v)
{
	m_ValueStatFinal->m_AttackSpeed.IncreaseAbsBonus(2.f*v);
	m_ValueStatFinal->m_Armour.IncreaseAbsBonus(7.f*v);
	m_ValueStatFinal->m_MovementSpeed.IncreaseAbsBonus(10.f*v);
	m_ValueStatFinal->m_ElectricArmour.IncreaseAbsBonus(5.f*v);
	m_PlayerActor->GetCharacterMovement()->MaxWalkSpeed = m_ValueStatFinal->m_MovementSpeed.m_fFinalValue;
}
void UPlayerStatManager::ApplyCharStat_Luck(int v)
{
	m_ValueStatFinal->m_SoulArmour.IncreaseAbsBonus(2.f*v);
}
void UPlayerStatManager::CancelCharStat_Str(int v)
{
	m_ValueStatFinal->m_HealthPoint.DecreaseAbsBonus(2.4f*v);
	m_ValueStatFinal->m_AttackDamage.DecreaseAbsBonus(1.f*v);
	m_ValueStatFinal->m_FireArmour.DecreaseAbsBonus(5.f*v);
	m_PlayerActor->OnHealthChangeBroadcast();
}
void UPlayerStatManager::CancelCharStat_Agil(int v)
{
	m_ValueStatFinal->m_AttackSpeed.DecreaseAbsBonus(2.f*v);
	m_ValueStatFinal->m_Armour.DecreaseAbsBonus(7.f*v);
	m_ValueStatFinal->m_MovementSpeed.DecreaseAbsBonus(10.f*v);
	m_ValueStatFinal->m_ElectricArmour.DecreaseAbsBonus(5.f*v);
	m_PlayerActor->GetCharacterMovement()->MaxWalkSpeed = m_ValueStatFinal->m_MovementSpeed.m_fFinalValue;
}
void UPlayerStatManager::CancelCharStat_Luck(int v)
{
	m_ValueStatFinal->m_SoulArmour.DecreaseAbsBonus(2.f*v);
}

void UPlayerStatManager::PerformEquipFuncPtr(E_EQUIPMENT equipType, int  v)
{
	(this->* (m_EquipFuncPtr[(int)equipType]))(v);
}

void UPlayerStatManager::PerformUnequipFuncPtr(E_EQUIPMENT equipType, int v)
{
	(this->* (m_UnequipFuncPtr[(int)equipType]))(v);
}

void UPlayerStatManager::SetCharStatToValue()
{
	ApplyCharStat_Str(m_CharStatFinal.m_Str.GetDefaultValue());
	ApplyCharStat_Agil(m_CharStatFinal.m_Agil.GetDefaultValue());
	ApplyCharStat_Luck(m_CharStatFinal.m_Luck.GetDefaultValue());
}