#pragma once

#include "CoreMinimal.h"
#include "StoredItem.h"
#include "Datas/DGRG_Struct.h"
#include "Blueprint/UserWidget.h"
#include "Datas/DataTableRowBase.h"

#include  "Components/SizeBox.h"
#include "Components/Image.h"

#include "Datas/DGRG_Macro.h"

#include "WidgetItemVisual.generated.h"

/**
 * 
 */

class UWidgetSlotGrid;
class UDragDropOperationItemVisual;

UCLASS()
class DGRG_2_API UWidgetItemVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	DECLARE_DELEGATE_TwoParams(FItemAndVisual, UStoredItem*, UWidgetItemVisual*)

	UWidgetItemVisual(const FObjectInitializer& ObjectInitializer);
protected:
	void SetItemRef(UStoredItem* item);
	void SetGridWidget(UWidgetSlotGrid* gridWidget);
	void SetPivot(FCoord pivt);
	void SetWrapSize(FCoord itemSize);
public:
	void RemoveItemFromInven();
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FBaseItemData& GetItemData() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UStoredItem* GetItemInstance() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UWidgetSlotGrid* GetGridWidget() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FCoord GetPivot() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetVisualWidget(FCoord pivt,UStoredItem* itemRef,UWidgetSlotGrid* gridWidget);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UDragDropOperationItemVisual* OnDragStart();
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	FItemAndVisual m_OnItemVisualClickUp;
	FVoidVoid m_OnItemVisualClickDown;
protected:
	UPROPERTY(VisibleAnywhere)
	UStoredItem* m_ItemRef;
	UPROPERTY(VisibleAnywhere)
	UWidgetSlotGrid* m_GridWidget;
	FCoord m_Pivot;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	USizeBox* m_MainSizeBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_IconImage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_IconBG;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDragDropOperationItemVisual> m_ClassDDOItmVisl;

};
