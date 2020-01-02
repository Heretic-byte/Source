// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StoredEquipItem.h"
#include "ItemContainer.h"
#include "EquipSlot.generated.h"

/**
 * 
 */
class APortraitRenderActor;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DGRG_2_API UEquipSlot : public UItemContainer
{
public:
	GENERATED_BODY()
	UEquipSlot();
protected:
	UPROPERTY(VisibleAnywhere)
	AActor* m_CurrentEquipitemActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName m_SlotSocketName;
	UPROPERTY(VisibleAnywhere)
	UStoredEquipItem* m_EquipItemInstance;

	E_EQUIPMENT m_CurrentEquipItem;
	bool m_IsOccupied;
	TArray<bool> m_AbleEquipSlot;
public:
	void SetEquipItem(UStoredEquipItem * EquipItemInstance);
	void SetUnEquipItem();

	virtual bool AddItemToPivot(FCoord pivot,   UStoredItem* dItem) override;
	virtual bool AddItemToEmptySpace(UStoredItem* dItem, FCoord& resultPivot) override;

	virtual bool RemoveItemFromPivot(FCoord pivot,  UStoredItem* dItem) override;
	virtual bool RemoveItemFromAuto( UStoredItem* dItem) override;

	UStoredEquipItem * GetCurrentEquippedData() const;
	AActor* GetCurrentEquipActor();
	FName GetSlotSocketName() const;
	E_EQUIPMENT GetCurrentEquipType();

	void SetSlotSocketName(FName nameWant);
	void SetOccupied(bool isOccupied);
	FORCEINLINE bool GetOccupied()
	{
		return m_IsOccupied;
	}
public:
	UPROPERTY(BlueprintAssignable,Category="Inventory")
	UStoredEquipItem::FEquipDelegate m_OnEquippedItem;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	UStoredEquipItem::FEquipDelegate m_OnUnequippedItem;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidVoidBP m_OnEquippedBP;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidVoidBP m_OnUnequippedBP;

protected:
	void CreateEquipMesh();
	virtual bool CheckAbleToEquip(UStoredEquipItem * equipItem);
public:
	bool CheckEquipSlotWithType(E_EQUIPMENT typeWant);
	void SetEquipSlotAble(E_EQUIPMENT typeWant, bool wantAble);
	void SetPortraitActor(APortraitRenderActor* portActor);
protected:
	APortraitRenderActor* m_PortraitActor;
};
//HEAD = 0x00000001,
//NECK = 0x00000002,
//TORSO = 0x00000004,
//BELT = 0x00000008,
//SHOE = 0x00000010,
//GLOVE = 0x00000020,
//RING = 0x00000040,
//ONEHAND = 0x00000080,
//SHIELD = 0x00000100,
//TWOHAND = 0x00000200,
//DAGGER = 0x00000400,
//KATANA = 0x00000800