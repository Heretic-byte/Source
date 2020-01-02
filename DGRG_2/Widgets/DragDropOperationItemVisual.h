// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Datas/DGRG_Struct.h"
#include "DragDropOperationItemVisual.generated.h"

/**
 * 
 */

class ADGRG_CombatCharacter;
class UStoredItem;
class UWidgetSlotGrid;
class UWidgetItemVisual;

UCLASS()
class DGRG_2_API UDragDropOperationItemVisual : public UDragDropOperation
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UStoredItem* m_ItemRef;
	UPROPERTY()
	UWidgetSlotGrid* m_PreGrid;
	UPROPERTY()
	UWidgetItemVisual* m_PreItemVisual;
	FCoord m_PrePivot;
public:
	//Get
	UFUNCTION(BlueprintCallable, Category = "Item")
	bool DropItemToGround(ADGRG_CombatCharacter* dropper);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UStoredItem* GetItemRef() {return m_ItemRef;}
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetSlotGrid* GetPreGrid() { return m_PreGrid; }
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE FCoord GetPrePivot() { return m_PrePivot; }


	UFUNCTION(BlueprintCallable,Category="Widget")
	void SetDragDropItemVisual(UStoredItem* itemRef, UWidgetSlotGrid* preGrid, FCoord prePivot, UWidgetItemVisual* defaultVisual);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void BackAddToPreGrid();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void RemovePreItemVisualFromInven();
};
