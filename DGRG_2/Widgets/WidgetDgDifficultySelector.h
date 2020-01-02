// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/DGRG_Enum.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WidgetDgDifficultySelector.generated.h"
class UDGRG_GameInstance;
class UDungeonManager;
/**
 * 
 */
UCLASS()
class DGRG_2_API UWidgetDgDifficultySelector : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Init();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void IncreaseDiffy();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DecreaseDiffy();
	UFUNCTION(BlueprintNativeEvent)
	void OnDiffyChanaged();
	virtual void OnDiffyChanaged_Implementation();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	const FText& GetDiffyName() const;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	FText GetDiffyText();
protected:
	void SetDiffyNameTextAry();
	FText SetDiffyName(int index);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_BtnDecrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_BtnIncrease;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDGRG_GameInstance* m_GameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDungeonManager* m_DungeonManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int m_CurrentDiffy;
	int m_Min;
	int m_Max;

	FText m_DiffyNames[(int)E_DIFFICULTY::LENGTH];
};
