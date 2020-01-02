// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDgMainEnter.generated.h"


class UWidgetDgStageSelector;
class UWidgetDgDifficultySelector;
class UWidgetDgThemeInfoShower;
/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetDgMainEnter : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetDgStageSelector* m_StageSelector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetDgDifficultySelector* m_DiffySelector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetDgThemeInfoShower* m_ThemeSelector;
public:
	UFUNCTION(BlueprintCallable,Category="Widget")
	void Init();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	UWidgetDgStageSelector* GetStageSelector();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void CloseDgEnterWidget();
};
