// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/DGRG_Struct.h"
#include "Blueprint/UserWidget.h"

#include "ItemContainer.h"
#include "StoredItem.h"

#include "Components/SizeBox.h"
#include "Components/GridPanel.h"

#include "WidgetItemVisual.h"
#include "WidgetSlot.h"
#include "DragAndDrop.h"



#include "WidgetSlotGrid.generated.h"
/**
 * 
 */

struct FGeometry;
struct FPointerEvent;
class UWidgetItemToolTip;
class UWidget;
class UWidgetMainMenu;
class UImage;

UCLASS()
class DGRG_2_API UWidgetSlotGrid : public UUserWidget
{
	GENERATED_BODY()
public:
	typedef void (UObject::*FPtrVisualClickUp)(UStoredItem*, UWidgetItemVisual*);
	typedef void (UObject::*FPtrVisualClickDown)(void);
protected:
	FCoord MouseToInvenIndex(FVector2D mouseCoord);
	FCoord GetTargetPivot(FCoord mouseCenter,UStoredItem* itemRef);
	void AddItemVisualToSlot(UWidgetItemVisual* itemVisual,FCoord pivot);
	void ClearGrid();
	void SetBoxSize(FCoord invenSize);
	void BindEventToItemContainer();
	UWidgetSlot* GetChildAtCoord(FCoord pivot);
public:
	void SetVisualToolTipClickUpFPtr(FPtrVisualClickUp fptr, UObject* giver);
	void SetVisualToolTipClickDownFPtr(FPtrVisualClickDown fptr, UObject* giver);
	TArray<UWidgetItemVisual*>& GetVisualArray();
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void CreateAddItemVisualWidget(UStoredItem* itemRef, FCoord pivot);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	bool OnDropOnSlot(FGeometry geo, FPointerEvent pEvent, class UDragDropOperation* ddo);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetWidgetSlotGrid(UItemContainer* itemCon);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetGrid(FCoord invenSize);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	bool AddItemToPivot(FCoord pivot, UStoredItem* itemRef);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	bool AddItemAuto(UStoredItem* itemRef);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UItemContainer* GetItemContainer() {return m_ItemContainer;}
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void UpdateGrid(UItemContainer* newItemCon);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetCoverImageToDefault();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetCoverImage(UTexture2D* newTexture);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ShowCoverImage();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void HideCoverImage();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetCoverImageTint(const FLinearColor& colorWant);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetCoverImageTintDefault() ;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_CoverImage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* m_SlotGridPanel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	USizeBox* m_DropSizeBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWidgetItemVisual> m_ClassWidgetItemVisual;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWidgetSlot> m_ClassWidgetSlot;
	UPROPERTY(VisibleAnywhere)
	UItemContainer* m_ItemContainer;
	UPROPERTY(VisibleAnywhere)
	UObject* m_FPtrClickUpGiver;
	UPROPERTY(VisibleAnywhere)
	UObject* m_FPtrClickDownGiver;
	UPROPERTY(VisibleAnywhere)
	UTexture2D* m_BaseIcon;
	UPROPERTY(VisibleAnywhere)
	TArray<UWidgetItemVisual*>  m_WidgetItemVisualArray;
protected:
	FPtrVisualClickUp m_FPtrItemVisualToolTipClickUp;
	FPtrVisualClickDown m_FPtrItemVisualToolTipClickDown;

};
