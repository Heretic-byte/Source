// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameInstanceSetter.h"
#include "DGRG_GameInstance.h"
#include "ManagerBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class DGRG_2_API UManagerBase : public UObject, public IGameInstanceSetter
{
	GENERATED_BODY()
public:
	UManagerBase();

	virtual void SetGameInstance(const UDGRG_GameInstance* gameInstance) override;

	virtual void Init(UDGRG_GameInstance* gameInstance);
protected:
	UPROPERTY(VisibleAnywhere)
	const UDGRG_GameInstance* m_GameInstance;


};
