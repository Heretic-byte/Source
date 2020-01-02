// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Datas/DGRG_DungeonThemeAsset.h"

#include "WidgetDgThemeInfoShower.generated.h"


class UDGRG_GameInstance;
class UDungeonManager;
UCLASS()
class DGRG_2_API UWidgetDgThemeInfoShower : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetDgThemeInfoShower(const FObjectInitializer& objInit);
	void Init();
public:
	UFUNCTION(BlueprintCallable)
	void ShowThemeInfo(const UDGRG_DungeonThemeAsset* themeAsset);
protected:
	UDGRG_GameInstance* m_GameInstance;
	UDungeonManager* m_DgManager;
};
