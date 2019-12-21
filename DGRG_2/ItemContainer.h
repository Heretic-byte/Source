// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "DataTableRowBase.h"
#include "StoredItem.h"
#include "Components/ActorComponent.h"
#include "ItemContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DGRG_2_API UItemContainer : public UActorComponent
{

public:
	GENERATED_BODY()
	UItemContainer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCoord m_InvenWidthHeight;
	//인벤할당만 해주는거
	TArray<TArray< UStoredItem* >> m_Container;

protected:


	bool SearchAbleSpaceAll( UStoredItem* item, FCoord* result);

	bool SearchAbleSpace(FCoord leftTop, FCoord rightBtm,   UStoredItem* item, FCoord* result);

	bool CheckCanbeAddItemAreaFast(FCoord leftTop, FCoord rightBtm);

	void SetInstacneToSlot(FCoord resultCoodPivot,   UStoredItem*  dItem);

	bool SetNullInstacneToSlot(FCoord leftTop,   UStoredItem* dItem);

public:
	FORCEINLINE FCoord GetInvenSize() { return m_InvenWidthHeight; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool AddItemToEmptySpace(  UStoredItem* dItem, FCoord& resultPivot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool AddItemToPivot(FCoord pivot,    UStoredItem* dItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool RemoveItemFromPivot(FCoord pivot,   UStoredItem* dItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool RemoveItemFromAuto(  UStoredItem* dItem);


	UStoredItem::FItemDelegate OnItemAdd;

	UStoredItem::FItemDelegate OnItemRemove;
	//

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CheckCanbeAddItemArea(FCoord leftTop,   UStoredItem* dItem);
	//
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PrintDebug();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetContainerSize(int width, int height);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetContainer();
};
