// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
//#include "DGRG_GameInstance.h"
#include "GameInstanceSetter.generated.h"

class UDGRG_GameInstance;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameInstanceSetter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DGRG_2_API IGameInstanceSetter
{
	GENERATED_BODY()

public:
	virtual void SetGameInstance(const UDGRG_GameInstance* gameInstance)  {}

};
