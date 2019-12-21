// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGRG_Enum.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WidgetMonsterInfo.generated.h"

/**
 *
 */

class AMonsterBase;
UCLASS()
class DGRG_2_API UWidgetMonsterInfo : public UUserWidget
{
	GENERATED_BODY()
	public:
	UWidgetMonsterInfo(const FObjectInitializer& ObjectInitializer);
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetMonsterInfo(AMonsterBase* monsterRef);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void SetHealthBar(float pecent1);
	virtual void SetHealthBar_Implementation(float pecent1);
	void SetHealth(float cHealth,float mHealth);
	UFUNCTION()
	void SetLevel(int level);
	void SetMonsterName(FText nameT);
	void SetMonsterType(E_ATTACKTYPE type);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_TextHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_TextMonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_TextType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_TextLevel;
protected:
	FText m_TypePhysical;
	FText m_TypeElectrical;
	FText m_TypeFire;
	FText m_TypeSoul;
	FTextFormat m_HealthFormat;
	UPROPERTY(VisibleAnywhere)
	AMonsterBase * m_CurrentMonster;
};
