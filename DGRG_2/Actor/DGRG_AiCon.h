// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "GenericTeamAgentInterface.h"






#include "DGRG_AiCon.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API ADGRG_AiCon : public AAIController
{
	GENERATED_BODY()
	
public:
	ADGRG_AiCon();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	void SetActive(bool b);
protected:
	//UPROPERTY()
	//FGenericTeamId m_TeamID;

	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
};
