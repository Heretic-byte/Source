// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StoredItem.h"
#include "StoredEquipItem.generated.h"


class UWidgetSlotGrid;
class AMonsterBase;
struct FItemTier;
struct FEquipmentItemData;
struct FOption;
struct FStatF;

UCLASS()
class DGRG_2_API UStoredEquipItem : public UStoredItem
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipDelegate, UStoredEquipItem*, item);

	UStoredEquipItem();
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetRandomItemStat(int level);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CalculateStat();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemLevel(int level);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetQualityRandom();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FStatF GetMainStat() { return m_MainItemStat; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetItemLevel() { return m_ItemLevel; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FOption>& GetOptionArrays();
public:
	const  FEquipmentItemData& GetEquipItemData() const;

	const FItemTier& GetItemTier() const;

	void SetItemTier(const FItemTier* itemTier);

	virtual const FColor& GetItemColor() override;

	virtual void SetItemData(const FBaseItemData * baseData) override;

	virtual bool UseItem(ADGRG_PlayerCon* playerCon) override;

	bool GetIsEquipped();

	void SetIsEquipped(bool equipped);
protected:
	bool TryMoveItemGrid(UWidgetItemVisual* targetItemVisual,UWidgetSlotGrid* targetMoveWantSlot);

	bool TrySwapItemGrid(UWidgetItemVisual* itemFromEquip, UWidgetItemVisual* itemFromInven);
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FStatF m_MainItemStat;
	UPROPERTY(VisibleAnywhere)
	UStoredItem* m_ItemInstanceCache;
protected:
	const FEquipmentItemData* m_EquipItemData;
	const FItemTier* m_ItemTier;
	FQuality m_ItemQuality;
	int m_ItemLevel;
	bool m_IsEquipped;
	TArray<FOption> m_Options;
};
