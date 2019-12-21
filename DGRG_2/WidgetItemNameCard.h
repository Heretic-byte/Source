// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/RetainerBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "WidgetItemNameCard.generated.h"

/**
 * 
 */



class UStoredItem;
UCLASS()
class DGRG_2_API UWidgetItemNameCard : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	URetainerBox* m_RetainerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* m_SizeBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_ButtonForPackText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ItemName;
public:
	UFUNCTION(BlueprintCallable,Category="Item")
	void SetItemName(UStoredItem* itemRef );
};
