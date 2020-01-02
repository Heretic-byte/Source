// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

// Sets default values
APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APortal::OpenLevel(int index)
{
	UGameplayStatics::OpenLevel(this, FName(*m_WorldWantOpen[index].GetAssetName()));
}

void APortal::LoadLevel(int index,bool visible)
{
	UGameplayStatics::LoadStreamLevel(this, FName(*m_WorldWantOpen[index].GetAssetName()), visible, false,FLatentActionInfo());

}
