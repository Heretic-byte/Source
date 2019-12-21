// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipSlot.h"
#include "WidgetSlotGrid.h"
#include "DGRG_Enum.h"
#include "WidgetSimpleStatShow.h"
#include "WidgetEquipWindow.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetEquipWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Equip")
	void SetEquipGrid(TArray<UEquipSlot*> equipSlotArray);

	FORCEINLINE TArray<UWidgetSlotGrid*>& GetWidgetEquipSlots()
	{
		return m_WidgetSlotArray;
	}

	void GetEquipableSlot(E_EQUIPMENT equipType, TArray<UWidgetSlotGrid*>& outerArray);

	FORCEINLINE UWidgetSimpleStatShow* GetSimpleShow()
	{
		return m_SimpleShow;
	}
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Head;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Necklace;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Torso;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Glove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_LeftRing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_RightRing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_LeftWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_RightWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Belt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSlotGrid* m_Shoe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UWidgetSimpleStatShow* m_SimpleShow;
protected:
	TArray< UWidgetSlotGrid*> m_WidgetSlotArray;
};
