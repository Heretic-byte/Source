// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StoredItem.h"
#include "StoredMaterialItem.generated.h"

/**
 * 
 */

struct FMaterialItemData;
UCLASS()
class DGRG_2_API UStoredMaterialItem : public UStoredItem
{
	GENERATED_BODY()
public:
	UStoredMaterialItem();

	FMaterialItemData* m_MatItemData;

	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FMaterialItemData* GetMatItemData() const;

	virtual void SetItemData(const FBaseItemData* baseData ) override ;
};
