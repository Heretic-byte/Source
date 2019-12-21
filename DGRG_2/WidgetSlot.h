// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSlot.generated.h"

/**
 * 
 */

class UWidgetItemVisual;
class UGridPanel;


UCLASS()
class DGRG_2_API UWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Widget")
	void AddItemVisual(UWidgetItemVisual* itemVisual);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* m_SlotGridPanel;
};
