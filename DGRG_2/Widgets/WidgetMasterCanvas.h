// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Anchors.h"

#include "Datas/DGRG_Macro.h"

#include "WidgetMasterCanvas.generated.h"
/**
 * 
 */

class UWidgetDgStageSelector;
class UWidgetMainMenu;
class AMonsterBase;
class UWidgetDgMainEnter;
UCLASS()
class DGRG_2_API UWidgetMasterCanvas : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetMasterCanvas(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* m_CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetMainMenu* m_MainMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* m_MonsterInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* m_DialogueWindow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* m_InteractInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetDgMainEnter* m_DgEnter;

	virtual void SynchronizeProperties() override;

public:
	UFUNCTION(BlueprintCallable,Category="Widget")
	void AddChild(UUserWidget* widget,FVector2D pos, FVector2D alignment);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetHealthBar(float gauge1);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetExpBar(float gauge1);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetStaminaBar(float gauge1);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetLevel(int lvl);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetGold(int amount);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetMonsterInfo( AMonsterBase* monster);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetHealthPotion(int amount);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetMonsterHealthBar(float gauge1);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowDialWindow();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideDialWindow();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowMonsterInfo();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideMonsterInfo();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowInteractInfo();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideInteractInfo();
	UFUNCTION()
	void DeleShowMonsterInfo(AMonsterBase* monster);
	UFUNCTION()
	void DeleHideMonsterInfo(AMonsterBase* monster);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowMouseCursor();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideMouseCursor();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ShowDgEnter();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HideDgEnter();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	UWidgetDgMainEnter* GetDgEnter();
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetMainMenu* GetMainMenu() { return m_MainMenu; }
public:
	FVoidVoid m_OnMainMenuOpen;
	FVoidVoid m_OnMainMenuClose;
};
