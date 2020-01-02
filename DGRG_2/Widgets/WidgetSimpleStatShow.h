// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSimpleStatShow.generated.h"

/**
 * 
 */

struct FStatDefault;

UCLASS()
class DGRG_2_API UWidgetSimpleStatShow : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetStat(FStatDefault& statFinal);

	UFUNCTION(BlueprintImplementableEvent,Category="Stat")
	void SetLevel(int v);
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Stat")
	void SetDmg(const FText& v);
	UFUNCTION(BlueprintImplementableEvent, Category = "Stat")
	void SetHp(const FText& v);
	UFUNCTION(BlueprintImplementableEvent, Category = "Stat")
	void SetArmor(const FText& v);
};
