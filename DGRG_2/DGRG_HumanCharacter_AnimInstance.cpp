// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_HumanCharacter_AnimInstance.h"
#include "DGRG_BaseCharacter.h"

void UDGRG_HumanCharacter_AnimInstance::SetMoveVector()
{
	m_MoveLength=GetOwner()->GetVelocity().Size();
}

ADGRG_BaseCharacter * UDGRG_HumanCharacter_AnimInstance::GetOwner()
{
	return Cast<ADGRG_BaseCharacter>(TryGetPawnOwner());
}

void UDGRG_HumanCharacter_AnimInstance::SetHitten()
{
	m_IsHitten=GetOwner()->GetIsHitten();
}