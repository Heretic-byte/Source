// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetProgressBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterialInterface* m_ProgressbarMat;

	UFUNCTION(BlueprintImplementableEvent, Category = "Stat")
	void OnNativeInit();
	
	virtual void NativeOnInitialized() override;


protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UMaterialInstanceDynamic* m_InstancedMat;
};
