// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Actor/DroppedItemActor.h"
#include "StoredItem.h"
#include "Actor/MonsterBase.h"
#include "Datas/DGRG_Macro.h"
#include "Datas/DGRG_Enum.h"
#include "Datas/DGRG_Struct.h"
#include "Datas/DataTableRowBase.h"
//
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
//
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerBase.h"


#include "Actor/DroppedGoldActor.h"

#include "ItemManager.generated.h"

/**
 * 
 */

class UDGRG_GameInstance;
UCLASS()
class DGRG_2_API UItemManager : public UManagerBase
{
	GENERATED_BODY()
public:
	typedef UStoredItem* (UItemManager::*FPtrItem)(const FBaseItemData&);
	UItemManager();
	UItemManager(const FObjectInitializer& ObjectInitializer);
	virtual void Init(UDGRG_GameInstance* gameInstance) override;
public:
	UStoredItem* CreateItemInstance(const FBaseItemData& itemData);
	void SpawnDropItemFromMonster(const AMonsterBase * monsterActor);
	const FItemTier& RollItemTier(const FItemTierRollRatio* rollPtr);
	bool CreateAndDropItemInRandomGround(FVector origin,float radius,UStoredItem* item);
	bool CreateAndDropGoldInRandomGround(FVector origin, float radius,int goldAmount );
protected:
	int GetCurrentItemLevel();
	const FItemTier& GetCurrentItemTier() const;
	void SetItemTierRollNull();
	void SetCurrentItemLevel(int nlvl);
	void SetCurrentItemTier(E_ITEMTIER tier);
	void SetItemTierRollPtr(const FItemTierRollRatio* rollPtr);
	void DropGoldFromMonster(const AMonsterBase * monsterActor);
	void DropItemFromMonster(const AMonsterBase * monsterActor);
	
	bool ItemDropRoll(const FDropItemData& itemData);
	bool GetRandomNavPoint(const FVector& monsterLocation, float radius, FVector& result);
	ADroppedItemActor* CreateDropItemActor(UStoredItem* itemInstance, FVector* point);
	ADroppedGoldActor* CreateDropGoldActor(int goldAmount, FVector* point);
	UStoredItem* CreateNormalItem(const FBaseItemData& itemData);
	UStoredItem* CreateEquipItem(const FBaseItemData& itemData);
	UStoredItem* CreateMaterialItem(const FBaseItemData& itemData);
	UStoredItem* PerformCreateItemFuncPtr(const FBaseItemData& itemData);
public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FVoidIntBP OnPotionAmountChange;
protected:
	const FItemTierRollRatio* m_CurrentItemTierRoll;
	const FItemTier* m_CurrentItemTier;
	int m_CurrentItemLevel;
	FPtrItem m_ItemSelect[(int)E_ITEMTYPE::LENGTH];
	FItemTierRollRatio m_DefaultRoll;
protected:
	UPROPERTY(EditDefaultsOnly,Category="Inventory")
	TSubclassOf<ADroppedItemActor> m_ClassDropItem;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<ADroppedGoldActor> m_ClassGoldItem;

};
