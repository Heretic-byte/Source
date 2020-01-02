// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetItemToolTip.h"
#include "Kismet/KismetTextLibrary.h"
#include "Internationalization.h"
#include "Actor/DGRG_PlayerCon.h"


void UWidgetItemToolTip::NativePreConstruct()
{
	Super::NativePreConstruct();
	m_OptionArray.Empty();
	m_OptionArray.Reserve(6);
	m_OptionArray.Emplace(m_TextOption1);
	m_OptionArray.Emplace(m_TextOption2);
	m_OptionArray.Emplace(m_TextOption3);
	m_OptionArray.Emplace(m_TextOption4);
	m_OptionArray.Emplace(m_TextOption5);
	m_OptionArray.Emplace(m_TextOption6);
	//m_ButtonClose->OnClicked.AddDynamic(this, &UWidgetItemToolTip::SetHideThisWindow);
	m_FormatItemStack = FTextFormat(FText::FromString("Quantity:{0}"));
	m_FormatSellPrice = FTextFormat(FText::FromString("Sell Price:{0}"));
	m_FormatItemLevel = FTextFormat(FText::FromString("Level:{0}"));


	//
	m_BrushMainStatDmg = FSlateBrush();
	m_BrushMainStatDmg.SetResourceObject(m_MainStatIconDmg);

	m_BrushMainStatHp = FSlateBrush();
	m_BrushMainStatHp.SetResourceObject(m_MainStatIconHp);

	m_BrushMainStatArmor = FSlateBrush();
	m_BrushMainStatArmor.SetResourceObject(m_MainStatIconArmor);

	m_BrushMainBaseItem = FSlateBrush();
	m_BrushMainBaseItem.SetResourceObject(m_MainIconBaseItem);

	m_BrushMainEnchantItem = FSlateBrush();
	m_BrushMainEnchantItem.SetResourceObject(m_MainIconEnchant);

	m_BrushMainMaterialItem = FSlateBrush();
	m_BrushMainMaterialItem.SetResourceObject(m_MainIconMaterial);

	m_BaseWhiteColor = FColor::White;
	m_Blank = FText();
	//배열포인터 하나로 통일
	//
	m_FPtrSelectItemType[(int)E_ITEMTYPE::NORMAL] = &UWidgetItemToolTip::SetBaseItemToolTip;
	m_FPtrSelectItemType[(int)E_ITEMTYPE::EQUIP] = &UWidgetItemToolTip::SetEquipItemToolTip;
	m_FPtrSelectItemType[(int)E_ITEMTYPE::MATERIAL] = &UWidgetItemToolTip::SetMaterialItemToolTip;
	m_FPtrSelectItemType[(int)E_ITEMTYPE::ENCHANT] = &UWidgetItemToolTip::SetEnchantItemToolTip;
	m_FPtrSelectItemType[(int)E_ITEMTYPE::GEM] = &UWidgetItemToolTip::SetGemItemToolTip;
//
	m_SetItemTierFPtrAry[(int)E_ITEMTIER::NORMAL] = &UWidgetItemToolTip::SetItemTierTextNormal;
	m_SetItemTierFPtrAry[(int)E_ITEMTIER::MAGIC] = &UWidgetItemToolTip::SetItemTierTextMagic;
	m_SetItemTierFPtrAry[(int)E_ITEMTIER::RARE] = &UWidgetItemToolTip::SetItemTierTextRare;
	m_SetItemTierFPtrAry[(int)E_ITEMTIER::EPIC] = &UWidgetItemToolTip::SetItemTierTextEpic;
	m_SetItemTierFPtrAry[(int)E_ITEMTIER::LEGEND] = &UWidgetItemToolTip::SetItemTierTextLegend;
	//얘는 슬롯별로 다나와야함
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::HEAD] = &UWidgetItemToolTip::SetSlotTextHead;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::TORSO] = &UWidgetItemToolTip::SetSlotTextTorso;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::BELT] = &UWidgetItemToolTip::SetSlotTextBelt;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::SHOE] = &UWidgetItemToolTip::SetSlotTextShoe;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::GLOVE] = &UWidgetItemToolTip::SetSlotTextGlove;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::SHIELD] = &UWidgetItemToolTip::SetSlotTextShield;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::NECK] = &UWidgetItemToolTip::SetSlotTextNeck;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::RING] = &UWidgetItemToolTip::SetSlotTextRing;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::ONEHAND] = &UWidgetItemToolTip::SetSlotTextOneHand;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::TWOHAND] = &UWidgetItemToolTip::SetSlotTextTwoHand;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::DAGGER] = &UWidgetItemToolTip::SetSlotTextDagger;
	m_SetItemEquipSlotFPtrAry[(int)E_EQUIPMENT::KATANA] = &UWidgetItemToolTip::SetSlotTextKatana;
	//메인스텟도 종류로 나눌것
	m_ButtonUse->OnClicked.AddDynamic(this, &UWidgetItemToolTip::UseItemByWidgetButton);
}

UWidgetItemToolTip::UWidgetItemToolTip(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
	
}

void UWidgetItemToolTip::SetItemToolTip(UStoredItem * item)
{
	(this->*(m_FPtrSelectItemType[(int)(item->GetItemData().m_ItemType)]))(item);
}

void UWidgetItemToolTip::SetHideThisWindow()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetItemToolTip::UseItemByWidgetButton()
{
	auto* PlayerCon= GetOwningPlayer<ADGRG_PlayerCon>();

	if (m_ItemUseDele.IsBound())
	{
		if (m_ItemUseDele.Execute(PlayerCon))
		{
			m_OnSuccess.ExecuteIfBound();
		}
	}

}


void UWidgetItemToolTip::SetMainStat(FText t)
{
	m_TextItemMainStat->SetText(t);
}

void UWidgetItemToolTip::ClearMainStat()
{
	m_TextItemMainStat->SetText(FText::FromString(""));
}

void UWidgetItemToolTip::SetOptionText(const TArray<FOption>& optionArys)
{
	int i = 0;
	while (i<optionArys.Num())
	{
		auto ASD = optionArys[i].ToText();
		m_OptionArray[i]->SetText(ASD);
		i++;
	}
}

void UWidgetItemToolTip::SetTextItemName(FText itemName)
{
	m_TextItemName->SetText(itemName);
}

void UWidgetItemToolTip::SetTextItemSellValue(int sellValue)
{
	FFormatOrderedArguments FormatT;
	FormatT.Add(sellValue);

	m_TextSellPrice->SetText(FText::Format(m_FormatSellPrice, FormatT));
}

void UWidgetItemToolTip::SetImageItemIcon(UTexture * itemIcon)
{
	FSlateBrush ItemIcon = FSlateBrush();
	ItemIcon.SetResourceObject(itemIcon);
	m_ImageItemIcon->SetBrush(ItemIcon);
}

void UWidgetItemToolTip::SetColorItemTier(const FColor & colorWant)
{
	m_BorderItemTierColorBG->SetBrushColor(colorWant);
	m_ImageItemTierColor->SetBrushTintColor(FSlateColor(colorWant));
	m_ImageItemIconTierBG->SetBrushTintColor(FSlateColor(colorWant));
	m_TextItemTier->SetColorAndOpacity(FSlateColor(colorWant));
}

void UWidgetItemToolTip::SetTextItemTier(const FItemTier & itemTier)
{
	(this->*(m_SetItemTierFPtrAry[(int)itemTier.m_TierName]))();
}

void UWidgetItemToolTip::SetTextItemLevel(int lv)
{
	FFormatOrderedArguments FormatT;
	FormatT.Add(lv);

	m_TextItemLevel->SetText(FText::Format(m_FormatItemLevel, FormatT));
}

void UWidgetItemToolTip::SetTextItemEquipSlot(E_EQUIPMENT equipSlot)
{
	(this->*(m_SetItemEquipSlotFPtrAry[(int)equipSlot]))();
}


void UWidgetItemToolTip::ClearOption()
{
	for (auto* OptionText : m_OptionArray)
	{
		OptionText->SetText(m_Blank);
	}
}

void UWidgetItemToolTip::ClearButtonDelegate()
{
	m_ButtonUse->OnClicked.Clear();
}

void UWidgetItemToolTip::SetTextItemDesc(FText itemDesc)
{
	m_TextDescription->SetText(itemDesc);
}

void UWidgetItemToolTip::SetTextItemCurrentStack(bool stackable, int itemStackCurrent)
{
	if (!stackable)
	{
		m_TextStack->SetText(m_Blank);
		return;
	}
	FFormatOrderedArguments FormatT;
	FormatT.Add(itemStackCurrent);
	m_TextStack->SetText(FText::Format(m_FormatItemStack, FormatT));
}

#pragma region FPtr

void UWidgetItemToolTip::SetItemTypeTextNormal()
{
	m_TextItemType->SetText(FText::FromString("Normal"));
}

void UWidgetItemToolTip::SetItemTypeTextEquip()
{
	m_TextItemType->SetText(FText::FromString("Equipment"));
}

void UWidgetItemToolTip::SetItemTypeTextEnchant()
{
	m_TextItemType->SetText(FText::FromString("Enchantment"));
}

void UWidgetItemToolTip::SetItemTypeTextGem()
{
	m_TextItemType->SetText(FText::FromString("Gem"));
}

void UWidgetItemToolTip::SetItemTypeTextMaterial()
{
	m_TextItemType->SetText(FText::FromString("Material"));
}

void UWidgetItemToolTip::SetItemTierTextNormal()
{
	m_TextItemTier->SetText(FText::FromString("Normal"));
}

void UWidgetItemToolTip::SetItemTierTextMagic()
{
	m_TextItemTier->SetText(FText::FromString("Magic"));
}

void UWidgetItemToolTip::SetItemTierTextRare()
{
	m_TextItemTier->SetText(FText::FromString("Rare"));
}

void UWidgetItemToolTip::SetItemTierTextEpic()
{
	m_TextItemTier->SetText(FText::FromString("Epic"));
}

void UWidgetItemToolTip::SetItemTierTextLegend()
{
	m_TextItemTier->SetText(FText::FromString("Legend"));
}

void UWidgetItemToolTip::SetSlotTextHead()
{
	m_TextEquipSlot->SetText(FText::FromString("Head"));
	SetIconMainArmor();
}

void UWidgetItemToolTip::SetSlotTextTorso()
{
	m_TextEquipSlot->SetText(FText::FromString("Body"));
	SetIconMainArmor();
}

void UWidgetItemToolTip::SetSlotTextBelt()
{
	m_TextEquipSlot->SetText(FText::FromString("Belt"));
	SetIconMainHp();
}

void UWidgetItemToolTip::SetSlotTextShoe()
{
	m_TextEquipSlot->SetText(FText::FromString("Shoes"));
	SetIconMainArmor();
}

void UWidgetItemToolTip::SetSlotTextGlove()
{
	m_TextEquipSlot->SetText(FText::FromString("Gloves"));
	SetIconMainArmor();
}

void UWidgetItemToolTip::SetSlotTextShield()
{
	m_TextEquipSlot->SetText(FText::FromString("Shield"));
	SetIconMainArmor();
}

void UWidgetItemToolTip::SetSlotTextNeck()
{
	m_TextEquipSlot->SetText(FText::FromString("Necklace"));
	SetIconMainHp();
}

void UWidgetItemToolTip::SetSlotTextRing()
{
	m_TextEquipSlot->SetText(FText::FromString("Ring"));
	SetIconMainHp();
}

void UWidgetItemToolTip::SetSlotTextOneHand()
{
	m_TextEquipSlot->SetText(FText::FromString("OneHand Main/Off Hand"));
	SetIconMainDmg();
}

void UWidgetItemToolTip::SetSlotTextTwoHand()
{
	m_TextEquipSlot->SetText(FText::FromString("TwoHand Main Hand"));
	SetIconMainDmg();
}

void UWidgetItemToolTip::SetSlotTextKatana()
{
	m_TextEquipSlot->SetText(FText::FromString("Katana Main Hand"));
	SetIconMainDmg();
}

void UWidgetItemToolTip::SetSlotTextDagger()
{
	m_TextEquipSlot->SetText(FText::FromString("Dagger Main/Off Hand"));
	SetIconMainDmg();
}

void UWidgetItemToolTip::SetIconMainDmg()
{
	m_ImageItemMainStatIcon->SetBrush(m_BrushMainStatDmg);
}

void UWidgetItemToolTip::SetIconMainHp()
{
	m_ImageItemMainStatIcon->SetBrush(m_BrushMainStatHp);
}

void UWidgetItemToolTip::SetIconMainArmor()
{
	m_ImageItemMainStatIcon->SetBrush(m_BrushMainStatArmor);
}
#pragma endregion
void UWidgetItemToolTip::SetBaseItemToolTip(UStoredItem * item)
{
	m_TextItemTier->SetColorAndOpacity(FSlateColor(m_BaseWhiteColor));
	SetTextItemName(item->GetItemData().m_Name);
	SetTextItemSellValue(item->GetItemData().m_nValue);
	SetTextItemDesc(item->GetItemData().m_Description);
	SetTextItemCurrentStack(item->GetItemData().m_Stackable, item->GetCurrentStack());
	SetImageItemIcon(item->GetItemData().m_Icon);
	SetColorItemTier(item->GetItemColor());
	ClearMainStat();
	SetItemTypeTextNormal();

	if(m_ItemUseDele.IsBound())
		m_ItemUseDele.Unbind();

	m_ItemUseDele.BindUObject(item, &UStoredItem::UseItem);

	SetUseButtonTextNormal();

	ClearOption();
}
void UWidgetItemToolTip::SetEquipItemToolTip(UStoredItem * item)
{
	SetBaseItemToolTip(item);
	//
	auto* equipItem = Cast<UStoredEquipItem>(item);
	SetMainStat(equipItem->GetMainStat().ToText(0));
	SetTextItemEquipSlot(equipItem->GetEquipItemData().m_EquipmentType);
	SetTextItemLevel(equipItem->GetItemLevel());
	SetTextItemTier(equipItem->GetItemTier());
	SetItemTypeTextEquip();
	SetUseButtonTextEquip(equipItem->GetIsEquipped());
	SetOptionText(equipItem->GetOptionArrays());
}
void UWidgetItemToolTip::SetEnchantItemToolTip(UStoredItem * item)
{
	SetBaseItemToolTip(item);
	SetItemTypeTextEnchant();
}
void UWidgetItemToolTip::SetGemItemToolTip(UStoredItem * item)
{
	SetBaseItemToolTip(item);
	SetItemTypeTextGem();
}
void UWidgetItemToolTip::SetMaterialItemToolTip(UStoredItem * item)
{
	SetBaseItemToolTip(item);
	SetItemTypeTextMaterial();
}

void UWidgetItemToolTip::ShowUseButton()
{
	m_ButtonUse->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWidgetItemToolTip::HideUseButton()
{
	m_ButtonUse->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetItemToolTip::SetUseButtonTextNormal()
{
	m_TextUse->SetText(FText::FromString( "Use"));
}

void UWidgetItemToolTip::SetUseButtonTextEquip(bool isEquipped)
{
	if (isEquipped)
	{
		m_TextUse->SetText(FText::FromString("UnEquip"));
		return;
	}
	m_TextUse->SetText(FText::FromString("Equip"));
}
