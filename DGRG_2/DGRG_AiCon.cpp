// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_AiCon.h"
#include "DGRG_BaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "BrainComponent.h"

ADGRG_AiCon::ADGRG_AiCon()
{
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ADGRG_AiCon::GetTeamAttitudeTowards(const AActor & Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}
	return ETeamAttitude::Neutral;
}

void ADGRG_AiCon::SetActive(bool b)
{
	BrainComponent->SetComponentTickEnabled(b);

	PerceptionComponent->SetComponentTickEnabled(b);
}

void ADGRG_AiCon::OnUnPossess()
{
	Super::OnUnPossess();
	Destroy();
}

void ADGRG_AiCon::BeginPlay()
{
	Super::BeginPlay();
}
