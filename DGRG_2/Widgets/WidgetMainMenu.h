// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CheckBox.h"
#include "WidgetEquipWindow.h"
#include "WidgetInventoryWindow.h"
#include "WidgetStatWindow.h"
#include "WidgetItemToolTip.h"
#include "WidgetMainMenu.generated.h"

class UWidgetItemVisual;
class UStoredItem;
class UWidgetItemToolTip;
class UPanelSlot;

UCLASS()
class DGRG_2_API UWidgetMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void InitConstruct();
protected:
	 void BindWindowUpdateToggle();
	 void BindDefaultToggle();
	 void InitToggle();
protected:
#pragma region WidgetP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Inven;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Status;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Skill;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_DungeonInfo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Quest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Shop;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Archive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* m_Option;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_EquipInvenParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetInventoryWindow* m_InvenWindow;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetEquipWindow* m_EquipWindow;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_StatusParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetStatWindow* m_StatWindow;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_SkillParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_DungeonParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_QuestParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_ShopParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_ArchiveParent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* m_OptionParent;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetItemToolTip* m_EquipMainToolTip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetItemToolTip* m_EquipSubToolTip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetItemToolTip* m_InvenToolTip;
	//
#pragma endregion
public:
	UFUNCTION(BlueprintCallable,Category="Widget")
	void ToggleExecptInven(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptStatus(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptSkill(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptDungeonInfo(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptQuest(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptShop(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptArchive(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ToggleExecptOption(bool state);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void HideAllToolTip();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void OpenInven();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void CloseInven();
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetInventoryWindow* GetInvenMenu() { return m_InvenWindow;}
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetEquipWindow* GetEquipMenu() { return m_EquipWindow; }
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetStatWindow* GetStatMenu() { return m_StatWindow; }
protected:
	UPROPERTY(VisibleAnywhere)
	UCheckBox* m_CurrentSelectToggle;
	UPROPERTY(VisibleAnywhere)
	UPanelWidget* m_CurrentSelectWindow;
protected:
	void ToggleWidget(UCheckBox* toggleBtn, UPanelWidget* parentWindow);

	void BoxDraw2(FPaintContext& cont, FVector2D point, float widthheight, FLinearColor color) const;

	void ShowEquipToolTip(UStoredItem* item, UWidgetItemVisual* visual);
	void ShowInvenToolTip(UStoredItem* item, UWidgetItemVisual* visual);

	void BindToolTipEquipInven();

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	FVector2D GetWidgetCenterLocation(UWidget * widget);
	FVector2D GetWidgetSize(UWidget * widget);
	void ModifyWidgetY(FVector2D & wantModify, FVector2D& theWidgetSize);

	void ShowEquipToolTipRight(UWidgetItemToolTip* toolTip, UWidgetItemVisual* visual);
	void ShowEquipToolTipLeft(UWidgetItemToolTip* toolTip, UWidgetItemVisual* visual);

private:
	FVector2D A;
	FVector2D B;
	FVector2D C;
};
