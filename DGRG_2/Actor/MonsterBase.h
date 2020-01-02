// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_BaseCharacter.h"
#include "Datas/DGRG_Macro.h"
#include "Components/WidgetComponent.h"
#include "MonsterBase.generated.h"

UCLASS()
class DGRG_2_API AMonsterBase : public ADGRG_BaseCharacter
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidMonsterBP, AMonsterBase*, monster);
public:
	AMonsterBase(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(EditAnyWhere,Category="Reward")
	float m_DropRadius;

	const FMonsterStatTable* m_MyData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	E_ATTACKTYPE m_Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	E_ITEMTIER m_CurrentTier;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	bool m_bManuallySet;


	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Interact")
	const FMonsterStatTable& GetMonsterData() const;
	virtual void GetKill() override;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetMonsterStat(int dgLevel, E_DIFFICULTY dgDifficult);
	void CalculatePrizeScaleFromPlayer();
	UFUNCTION(BlueprintCallable, Category = "Interact")
		FORCEINLINE E_ATTACKTYPE GetCurrentType() const{
		return m_Type;
	}
	UFUNCTION(BlueprintCallable, Category = "Interact")
	FORCEINLINE E_ITEMTIER GetCurrentTier() const{
		return m_CurrentTier;
	};
	FORCEINLINE float GetCurrentDropRadius() const{
		return m_DropRadius;
	};

protected:
	void SetSizeScale(float v);

	UPROPERTY(BlueprintAssignable,Category="Combat")
	FVoidMonsterBP OnMonsterKilled;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Combat")
	UWidgetComponent* m_HealthBarComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UTexture2D* m_IconThumbnail;

public:
	virtual void SetActive(bool b) override;
};
