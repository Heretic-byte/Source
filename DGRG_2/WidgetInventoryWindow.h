// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSlotGrid.h"
#include "ItemContainer.h"
#include "WidgetInventoryWindow.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetInventoryWindow : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_InventorySlotGrid;
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetInven(UItemContainer* itemCon);
	UFUNCTION(BlueprintCallable, Category = "Widget")
		FORCEINLINE UItemContainer* GetInvenInstance() {
		return m_InvenInstance;
	}
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetSlotGrid* GetInvenGrid() {
		return m_InventorySlotGrid;
	}
protected:
	UPROPERTY(VisibleAnywhere)
	UItemContainer* m_InvenInstance;
};
