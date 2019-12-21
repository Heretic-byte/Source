// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"

// Sets default values
UInteractable::UInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	m_Unlocked = true;
}


void UInteractable::Interact(AActor* interMan)
{
	if (!m_Unlocked)
	{
		OnCantInteractBP.Broadcast(interMan);
		return;
	}
	OnInteractBP.Broadcast(interMan);
}

void UInteractable::SetLock()
{
	m_Unlocked = false;
	OnLockedBP.Broadcast();
}

void UInteractable::SetUnlock()
{
	m_Unlocked = true;
	OnUnlockedBP.Broadcast();
}

void UInteractable::SetFocusIn()
{
	OnFocusInBP.Broadcast();
}

void UInteractable::SetFocusOut()
{
	OnFocusOutBP.Broadcast();
}


