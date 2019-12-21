// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_DestPoint = nullptr;
}

// Called when the game starts or when spawned

void ADoor::OpenDoorToMove(ADGRG_BaseCharacter* character)
{
	

	if (!m_DestPoint)
	{
		PRINTF("DestPoint Null");
		return;
	}

	OnEnterDoor.Broadcast(character);

	if (character->SetActorLocation(m_DestPoint->GetActorLocation(), false))
	{

	//OnEnterDoor.BroadCast(character);
	}
}
