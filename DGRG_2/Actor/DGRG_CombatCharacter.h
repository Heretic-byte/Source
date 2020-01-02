// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_BaseCharacter.h"
#include "Inventory.h"
#include "EquipSlot.h"
#include "DGRG_CombatCharacter.generated.h"

/**
 * 동아리 캐릭터들,인벤토리 및 equip가능
 */

class UStoredItem;
class UStoredEquipItem;
UCLASS()
class DGRG_2_API ADGRG_CombatCharacter : public ADGRG_BaseCharacter
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FStanceChanged, E_STANCE);
	typedef void (ADGRG_CombatCharacter::*FPtrForStance)(void);
	ADGRG_CombatCharacter(const FObjectInitializer& ObjectInitializer);
	void SetEquipSlotsArray();
	void SetStanceFPtr();
	void SetSlotsSocketName();
	void SetSlotsSize();
	void SetSlotsEquipableType();
	void CreateComponents();
#pragma region InvenEquip

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventory* m_Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotHead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotTorso;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotBelt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotShoe;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotNecklace;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotLeftRing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotRightRing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotLeftWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipSlot* m_EquipSlotRightWeapon;
public:
	TArray<UEquipSlot*>& GetEquipSlotArray();

public:
	UStoredItem::FItemDelegate m_OnAddItem;
	UStoredItem::FItemDelegate m_OnRemoveItem;
	ADGRG_CombatCharacter::FStanceChanged m_OnStanceChanged;
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToEmptySpace( UStoredItem* dItem, FCoord& resultPivot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToPivot(FCoord pivot,   UStoredItem* dItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemFromPivot(FCoord pivot,  UStoredItem* dItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemFromAuto( UStoredItem* dItem);
	//
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool DropItemGround(UStoredItem* dItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE	UInventory* GetInven()
	{
		return m_Inventory;
	}
#pragma endregion

protected:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CalculateStance();
	void ChangeStance();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Equipment)
	TArray<TSubclassOf<UDGRG_HumanCharacter_AnimInstance>> m_AnimSets;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Equipment)
	E_STANCE m_CurrentStance;

	FPtrForStance m_StanceFPtr[(int)E_EQUIPMENT::KATANA+1][(int)E_EQUIPMENT::KATANA+1];

	TArray<UEquipSlot*> m_EquipSlotArray;

	void SetStanceAllNull();
	void SetStanceNull();
	void SetStanceOneHand();
	void SetStanceDual();
	void SetStanceShield();
	void SetStanceDagger();
	void SetStanceKatana();
	void SetStanceTwoHand();

};
