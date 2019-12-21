// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "WidgetMasterCanvas.h"
#include "Anchors.h"

#include "DGRG_PlayerCon.generated.h"

class APlayerCharacter;
class UDGRG_GameInstance;

/**
 * 
 */
UCLASS()
class DGRG_2_API ADGRG_PlayerCon : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
		ADGRG_PlayerCon();
		ADGRG_PlayerCon(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	void SetPlayerDelegate();
	void SetManagerDelegate();
protected:
	FGenericTeamId m_TeamId;
	FDelegateHandle m_OnMonsterHpDeleHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Widget")
	UWidgetMasterCanvas* m_MasterWidget;
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	TSubclassOf<UWidgetMasterCanvas> m_ClassMWidget;
	UPROPERTY(VisibleAnywhere)
	AMonsterBase* m_CurrentAttackTarget;
	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* m_PlayerChar;
	UPROPERTY(VisibleAnywhere)
	UDGRG_GameInstance* m_GameManager;
public:
	FGenericTeamId GetGenericTeamId() const;
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void AddChild(UUserWidget * widget, FVector2D pos, FVector2D alignment);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackTargetFound(AMonsterBase* target);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	FORCEINLINE UWidgetMasterCanvas* GetMasterWidget()
	{
		return m_MasterWidget;
	}
};
