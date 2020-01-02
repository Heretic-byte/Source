// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Datas/DGRG_Struct.h"


#include "WidgetStatWindow.generated.h"

class UDGRG_GameInstance;
class UPlayerStatManager;
class UExpManager;

UCLASS()
class DGRG_2_API UWidgetStatWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetStatWindow(const FObjectInitializer& ObjectInitializer);
protected:
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_StrUpgradeButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_AgilUpgradeButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* m_LuckUpgradeButton;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_StrBonusText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_StrDefaultText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_AgilBonusText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_AgilDefaultText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_LuckBonusText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_LuckDefaultText;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ArmorText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_FireArmorText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ElecArmorText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_SoulArmorText;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ASpeedText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_MSpeedText;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_BonusExpText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_BonusGoldText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_BonusItemText;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ConstTextCoreStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ConstTextResistance;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_DmgText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_HpText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_ExpText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_RemainExpText;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_RemainStat;
protected:
	UPROPERTY(VisibleAnywhere)
	UDGRG_GameInstance* m_GameInstance;
	UPROPERTY(VisibleAnywhere)
	UPlayerStatManager* m_StatManager;
	UPROPERTY(VisibleAnywhere)
	UExpManager* m_ExpManager;
public:
	UFUNCTION()
	void UpdateOnWindowToggled(bool isSelected);
	UFUNCTION()
	void UpdateStatWindowAll();
	//일단은 이것만 써보자
protected:
	void SetStrText();
	void SetStrBonusText();
	void SetAgilText();
	void SetAgilBonusText();
	void SetLuckText();
	void SetLuckBonusText();
	void SetArmorText();
	void SetFireArmorText();
	void SetElecArmorText();
	void SetSoulArmorText();
	void SetAttackSpeedText();
	void SetMoveSpeedText();
	void SetExpText();
	void SetRemainExpText();
	void SetDmgText();
	void SetHpText();
	//
	void SetConstTextCoreStat();
	void SetConstTextResistance();
	//
	void SetBonusItemText();
	void SetBonusExpText();
	void SetBonusGoldText();
	//
	void SetRemainStatText();
protected:
	FTextFormat m_ConstBonusStat;
	//
	FTextFormat m_ConstArmor;
	FTextFormat m_ConstFArmor;
	FTextFormat m_ConstEArmor;
	FTextFormat m_ConstSArmor;
	//
	FTextFormat m_ConstExpText;
	FTextFormat m_ConstRemainExpText;
	//
	FText m_ConstCoreStat;
	FText m_ConstResistance;
	//
	FTextFormat m_ConstHealth;
	FTextFormat m_ConstDmg;
	FTextFormat m_ConstASpeed;
	FTextFormat m_ConstMSpeed;
	//
	FTextFormat m_ConstItemBonus;
	FTextFormat m_ConstExpBonus;
	FTextFormat m_ConstGoldBonus;
	//
	FTextFormat m_ConstRemainStatPoint;
public:
	//method
	void SetGameInstance(UDGRG_GameInstance* gameManager);
protected:
	void SetBinding();
};
