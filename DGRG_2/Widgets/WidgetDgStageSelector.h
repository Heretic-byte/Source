// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WidgetDgStageSelector.generated.h"


class UDGRG_GameInstance;
class UDungeonManager;
class APlayerCharacter;
class UDGRG_DungeonThemeAsset;
/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetDgStageSelector : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetDgStageSelector(const FObjectInitializer& objInit);
	UFUNCTION(BlueprintCallable)
	void Init();
public:
	UFUNCTION(BlueprintCallable)
	void IncreaseStageLevel();
	UFUNCTION(BlueprintCallable)
	void DecreaseStageLevel();
	UFUNCTION(BlueprintCallable)
	void EnterTheDungeon();
	UFUNCTION()
	void OnDungeonBuildComplete();
	UFUNCTION(BlueprintNativeEvent)
	void OnStageChanged();
	virtual void OnStageChanged_Implementation();
	UFUNCTION(BlueprintImplementableEvent)
	void OnThemeChanged(const UDGRG_DungeonThemeAsset* themeAsset);
protected:
	UPROPERTY()
	UDGRG_GameInstance* m_GameInstance;
	UPROPERTY()
	UDungeonManager* m_DungeonManager;
	UPROPERTY()
	APlayerCharacter* m_PlayerActor;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int m_CurrentStage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_BtnDecrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_BtnIncrease;
protected:
	int CalculateStageToMobLevel();
	void SetStageMobTheme(int resultStage);
};
