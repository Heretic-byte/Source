// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGroundActor.h"
#include "DGRG_2.h"
#include "DGRG_CombatCharacter.h"
// Sets default values
AItemGroundActor::AItemGroundActor()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldRoot"));
	m_SphereColl= CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	m_SphereColl->SetupAttachment(RootComponent);
	m_SphereColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_SphereColl->SetCollisionObjectType(ECC_GameTraceChannel3);
	//FCollisionObjectQueryParams CollObject= FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_GameTraceChannel3));
}

ADGRG_CombatCharacter * AItemGroundActor::GetCombatCharacter(AActor* interMan)
{
	return Cast<ADGRG_CombatCharacter>(interMan);;
}

void AItemGroundActor::SetScale(float per=1.0f)
{
	if (per <= 0)
	{
		PRINTF("Scale Can't Be Lessthan 0");
		return;
	}

	SetActorScale3D(FVector(per, per, per));
}
