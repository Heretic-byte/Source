// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DroppedItemActor.h"
#include "StoredItem.h"
#include "MonsterBase.h"
#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "DGRG_Struct.h"
#include "DataTableRowBase.h"
//
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavArea.h"
#include "NavigationData.h"
//
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerBase.h"
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

public:
	UPROPERTY(BlueprintAssignable,Category="Inventory")
	FVoidIntBP OnPotionAmountChange;

public:
	virtual void Init(UDGRG_GameInstance* gameInstance) override;

	void SpawnDropItemFromMonster(const AMonsterBase * monsterActor);

	void RollItemTier();
	
	void SetCurrentItemTier(E_ITEMTIER tier);

	const FItemTier& GetCurrentItemTier() const;

	void SetItemTierRollPtr(const FItemTierRollRatio* rollPtr);

	void SetItemTierRollNull();

	void SetCurrentItemLevel(int nlvl);

	int GetCurrentItemLevel();

	UStoredItem* CreateItemInstance(const FBaseItemData& itemData);

	bool CreateAndDropItemInRandomGround(FVector origin,float radius,UStoredItem* item);

protected:
	const FItemTierRollRatio* m_CurrentItemTierRoll;
	const FItemTier* m_CurrentItemTier;
	int m_CurrentItemLevel;
	UPROPERTY(EditDefaultsOnly,Category="Inventory")
	TSubclassOf<ADroppedItemActor> m_ClassDropItem;
	FPtrItem m_ItemSelect[(int)E_ITEMTYPE::LENGTH];
	FItemTierRollRatio m_DefaultRoll;

protected:
	bool ItemDropRoll(const FDropItemData& itemData);

	bool GetRandomNavPoint(const FVector& monsterLocation, float radius, FVector& result);

	ADroppedItemActor* CreateDropItemActor( UStoredItem* itemInstance, FVector* point);

	UStoredItem* CreateNormalItem(const FBaseItemData& itemData);
	UStoredItem* CreateEquipItem(const FBaseItemData& itemData);
	UStoredItem* CreateMaterialItem(const FBaseItemData& itemData);

	UStoredItem* PerformCreateItemFuncPtr(const FBaseItemData& itemData);


};
