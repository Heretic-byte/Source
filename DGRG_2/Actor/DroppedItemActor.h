// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemGroundActor.h"
#include "DroppedItemActor.generated.h"

/**
 * 루트 컴포넌트 읹
 */
class UStoredItem;

UCLASS()
class DGRG_2_API ADroppedItemActor : public AItemGroundActor
{
	GENERATED_BODY()
public:
		ADroppedItemActor(const FObjectInitializer& ObjectInitializer);
protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
		UStoredItem* m_CurrentItemInstance;
public:
		UFUNCTION(BlueprintCallable,Category = "Item")
		virtual void SetItemData( UStoredItem* itemData);
protected:
		void SetWidgetNameCard(UStoredItem * itemData);
		virtual void IfManualSet() override;
		virtual void AddItemToActor(AActor* interMan) override;
};
