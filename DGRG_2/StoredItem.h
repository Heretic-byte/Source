// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Datas/DGRG_Macro.h"

#include "UObject/NoExportTypes.h"
#include "Datas/DGRG_Struct.h"
#include "GameInstanceSetter.h"
//
//
#include "StoredItem.generated.h"

struct FBaseItemData;
class UDGRG_GameInstance;
class ADGRG_PlayerCon;
class UWidgetItemVisual;

UCLASS(BlueprintType)
class DGRG_2_API UStoredItem : public UObject
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FItemDelegate, UStoredItem*,  FCoord);
public:
	UStoredItem();
public:
	const FBaseItemData& GetItemData() const;

	virtual void SetItemData(const FBaseItemData * baseData);

	int GetCurrentStack();

	virtual const FColor&  GetItemColor();
	
	UWidgetItemVisual* GetItemVisualWidget();

	void SetItemVisualWidget(UWidgetItemVisual* visualWidget);
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool UseItem(ADGRG_PlayerCon* playerCon);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FCoord& GetItemSize();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int m_CurrentStackCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCoord m_WidthHeight;
protected:
	const FBaseItemData* m_ItemData;
	FColor m_BaseWhiteColor;
	UWidgetItemVisual* m_MyWidgetVisual;

};
