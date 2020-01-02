// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Datas/DGRG_Struct.h"
#include "Datas/DataTableRowBase.h"
#include "StoredEquipItem.h"
#include "StoredMaterialItem.h"
#include "Datas/DGRG_Enum.h"
#include "WidgetItemToolTip.generated.h"


class ADGRG_PlayerCon;
/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetItemToolTip : public UUserWidget
{
	GENERATED_BODY()
public:
	typedef void(UWidgetItemToolTip::*FPtrVoidVoid)(void);
	typedef void(UWidgetItemToolTip::*FPtrItem)(UStoredItem*);
	DECLARE_DELEGATE_RetVal_OneParam(bool,FItemUseDele ,ADGRG_PlayerCon*);
	DECLARE_DELEGATE(FOnSuccess);
	virtual void NativePreConstruct() override;
	UWidgetItemToolTip(const FObjectInitializer& ObjectInitializer);
protected:
#pragma region WidgetBind
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UBorder* m_BorderItemTierColorBG;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_ImageItemTierColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextItemType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_ImageItemIconTierBG;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_ImageItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* m_ImageItemMainStatIcon;//장비템일경우 방패 칼 바뀜,일반템이면?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextItemMainStat;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextItemTier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextEquipSlot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextItemLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextStack;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextOption6;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextSellPrice;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UButton* m_ButtonClose;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UButton* m_ButtonUse;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* m_TextUse;
#pragma endregion
public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetItemToolTip(UStoredItem* item);
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetHideThisWindow();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void UseItemByWidgetButton();
public:
	FOnSuccess m_OnSuccess;
protected:
#pragma region Setters
	void SetMainStat(FText t);
	void ClearMainStat();
	void SetOptionText(const TArray<FOption>& optionArys);


	void SetTextItemName(FText itemName);
	void SetTextItemSellValue(int sellValue);
	void SetTextItemDesc(FText itemDesc);
	void SetTextItemCurrentStack(bool stackable,int itemStackCurrent);
	void SetImageItemIcon(UTexture* itemIcon);
	//Equip
	void SetColorItemTier(const FColor& colorWant);
	void SetTextItemTier(const FItemTier& itemTier);
	void SetTextItemLevel(int lv);
	void SetTextItemEquipSlot(E_EQUIPMENT equipSlot);
	//void SetOption();
	void ClearOption();
	//
	void ClearButtonDelegate();

	void SetItemTypeTextNormal();
	void SetItemTypeTextEquip();
	void SetItemTypeTextEnchant();
	void SetItemTypeTextGem();
	void SetItemTypeTextMaterial();
	//
	void SetItemTierTextNormal();
	void SetItemTierTextMagic();
	void SetItemTierTextRare();
	void SetItemTierTextEpic();
	void SetItemTierTextLegend();
	//
	void SetSlotTextHead();
	void SetSlotTextTorso();
	void SetSlotTextBelt();
	void SetSlotTextShoe();
	void SetSlotTextGlove();
	void SetSlotTextShield();
	void SetSlotTextNeck();
	void SetSlotTextRing();
	void SetSlotTextOneHand();
	void SetSlotTextTwoHand();
	void SetSlotTextKatana();
	void SetSlotTextDagger();
	//
	void SetIconMainDmg();
	void SetIconMainHp();
	void SetIconMainArmor();
	//
	void SetBaseItemToolTip(UStoredItem* item);
	void SetEquipItemToolTip(UStoredItem* item);
	void SetEnchantItemToolTip(UStoredItem* item);
	void SetGemItemToolTip(UStoredItem* item);
	void SetMaterialItemToolTip(UStoredItem* item);
	//
	void ShowUseButton();
	void HideUseButton();
	void SetUseButtonTextNormal();
	void SetUseButtonTextEquip(bool isEquipped);
#pragma endregion

protected:
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	UTexture* m_MainStatIconDmg;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UTexture* m_MainStatIconHp;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UTexture* m_MainStatIconArmor;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UTexture* m_MainIconBaseItem;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UTexture* m_MainIconEnchant;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UTexture* m_MainIconMaterial;
protected:
	FText m_Blank;
	TArray<UTextBlock*> m_OptionArray;
	FTextFormat m_FormatItemStack;
	FTextFormat m_FormatSellPrice;
	FTextFormat m_FormatItemLevel;

	FSlateBrush m_BrushMainStatDmg;
	FSlateBrush m_BrushMainStatHp;
	FSlateBrush m_BrushMainStatArmor;
	FSlateBrush m_BrushMainBaseItem;
	FSlateBrush m_BrushMainEnchantItem;
	FSlateBrush m_BrushMainMaterialItem;
	FColor m_BaseWhiteColor;
	//
protected:
	FPtrVoidVoid m_SetItemTierFPtrAry[(int)E_ITEMTIER::LENGTH];
	FPtrVoidVoid m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::LEGNTH];
	FPtrItem m_FPtrSelectItemType[(int)E_ITEMTYPE::LENGTH];
	FItemUseDele m_ItemUseDele;
};
