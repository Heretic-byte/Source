// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Datas/DGRG_Macro.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerBase.h"
#include "Datas/DGRG_Struct.h"
#include "Actor/DGRG_CombatCharacter.h"
#include "Datas/DGRG_Enum.h"
#include "PlayerStatManager.generated.h"

/**
 * 
 */
class UStoredEquipItem;
class UDGRG_GameInstance;
UCLASS()
class DGRG_2_API UPlayerStatManager : public UManagerBase
{
public:
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam(FOnValueStat, FStatDefault&);
	typedef void (UPlayerStatManager::*FPtr)(float);
	UPlayerStatManager();
	UPlayerStatManager(const FObjectInitializer& ObjectInitializer);
public:
	virtual void Init(UDGRG_GameInstance* gameInstance) override;
	void SetPlayerActor(ADGRG_CombatCharacter* actorP);
	void SetFuncPtr();
public://uactions
	UFUNCTION(BlueprintCallable, Category = "Stat")
	void GainStatLevelUp();
	UFUNCTION(BlueprintCallable, Category = "Stat")
	void GainStatPoint(int amount);
	UFUNCTION(BlueprintCallable, Category = "Stat")
		FORCEINLINE FStatDefault& GetFinalStat() {
		return *m_ValueStatFinal;
	}
	UFUNCTION(BlueprintCallable, Category = "Stat")
	FORCEINLINE FStatChar& GetFinalCharStat() {
		return m_CharStatFinal;
	}
	UFUNCTION(BlueprintCallable, Category = "Combat")
	FORCEINLINE ADGRG_CombatCharacter* GetPlayerChar() {
		return m_PlayerActor;
	}
	UFUNCTION(BlueprintCallable, Category = "Stat")
	FORCEINLINE int GetRemainStatPoint() {
		return m_CurrentAvailableStats;
	}
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpgradeStatStr();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpgradeStatAgil();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UpgradeStatLuck();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ModifyEquipItem(UStoredEquipItem* equipItem);
	void UpdateWidget();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ModifyUnequipItem(UStoredEquipItem* equipItem);
public:
	UPROPERTY(BlueprintAssignable, Category = "Stat")
	FVoidVoidBP m_OnStatWindowChanged;
public://valueStat
#pragma region ModifyStats
	void IncreaseAbsDamage(float dmg);
	void IncreaseAbsArmor(float armor);
	void IncreaseAbsHp(float hp);
	void IncreasePerDamage(float dmg);
	void IncreasePerArmor(float armor);
	void IncreasePerHp(float hp);
	void DecreaseAbsDamage(float dmg);
	void DecreaseAbsArmor(float armor);
	void DecreaseAbsHp(float hp);
	void DecreasePerDamage(float dmg);
	void DecreasePerArmor(float armor);
	void DecreasePerHp(float hp);
	//
	void IncreaseAbsAttackSpeed(float v);
	void IncreasePerAttackSpeed(float v);
	void IncreaseAbsMoveSpeed(float v);
	void IncreasePerMoveSpeed(float v);
	void IncreaseAbsFireArmor(float v);
	void IncreasePerFireArmor(float v);
	void IncreaseAbsElecArmor(float v);
	void IncreasePerElecArmor(float v);
	void IncreaseAbsSoulArmor(float v);
	void IncreasePerSoulArmor(float v);
	void IncreasePerExpScale(float v);
	void IncreasePerDropRate(float v);
	void IncreasePerGoldScale(float v);
	//
	void DecreaseAbsAttackSpeed(float v);
	void DecreasePerAttackSpeed(float v);
	void DecreaseAbsMoveSpeed(float v);
	void DecreasePerMoveSpeed(float v);
	void DecreaseAbsFireArmor(float v);
	void DecreasePerFireArmor(float v);
	void DecreaseAbsElecArmor(float v);
	void DecreasePerElecArmor(float v);
	void DecreaseAbsSoulArmor(float v);
	void DecreasePerSoulArmor(float v);
	void DecreasePerExpScale(float v);
	void DecreasePerDropRate(float v);
	void DecreasePerGoldScale(float v);
#pragma endregion

public://charStat
	void IncreaseDefaultCharStat_Str(int v);
	void IncreaseDefaultCharStat_Agil(int v);
	void IncreaseDefaultCharStat_Luck(int v);
	void DecreaseDefaultCharStat_Str(int v);
	void DecreaseDefaultCharStat_Agil(int v);
	void DecreaseDefaultCharStat_Luck(int v);
	void CancelCharStat_Luck(int v);
	//
	void IncreaseBonusCharStat_Str(int v);
	void IncreaseBonusCharStat_Agil(int v);
	void IncreaseBonusCharStat_Luck(int v);
	void DecreaseBonusCharStat_Str(int v);
	void CancelCharStat_Str(int v);
	void DecreaseBonusCharStat_Agil(int v);
	void CancelCharStat_Agil(int v);
	void DecreaseBonusCharStat_Luck(int v);
protected:
	void ApplyCharStat_Str(int v);
	void ApplyCharStat_Agil(int v);
	void ApplyCharStat_Luck(int v);
public://c actions
	FOnValueStat m_OnFinalStatUpdated;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Combat")
	int m_LevelUpPerStatGain;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	int m_CurrentAvailableStats;
	UPROPERTY(VisibleAnywhere)
	ADGRG_CombatCharacter* m_PlayerActor;
protected:
	FStatChar m_CharStatFinal;
	FStatDefault* m_ValueStatFinal;
	FPtr m_EquipFuncPtr[(int)E_EQUIPMENT::LEGNTH];
	FPtr m_UnequipFuncPtr[(int)E_EQUIPMENT::LEGNTH];
protected:
	void SetCharStatToValue();
	void PerformEquipFuncPtr(E_EQUIPMENT equipType, int v);
	void PerformUnequipFuncPtr(E_EQUIPMENT equipType, int v);
};
