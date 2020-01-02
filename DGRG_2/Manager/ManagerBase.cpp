// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerBase.h"

UManagerBase::UManagerBase()
{

}

void UManagerBase::SetGameInstance(const UDGRG_GameInstance* gameInstance)
{
	m_GameInstance = gameInstance;
}

void UManagerBase::Init(UDGRG_GameInstance * gameInstance)
{
	SetGameInstance(gameInstance);
}
