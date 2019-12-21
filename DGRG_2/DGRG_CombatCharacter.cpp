// Fill out your copyright notice in the Description page of Project Settings.


#include "DGRG_CombatCharacter.h"
#include "StoredItem.h"
#include "Delegate.h"
#include "DGRG_GameInstance.h"
#include "StoredEquipItem.h"


ADGRG_CombatCharacter::ADGRG_CombatCharacter()
{
	m_CurrentStance = E_STANCE::EMPTY;
	m_AnimSets.Init(nullptr, (int)(E_STANCE::LENGTH));

	CreateComponents();
	SetSlotsEquipableType();
	SetSlotsSize();
	SetSlotsSocketName();

	m_EquipSlotLeftWeapon->m_OnEquippedBP.AddDynamic(this, &ADGRG_CombatCharacter::CalculateStance);
	m_EquipSlotLeftWeapon->m_OnUnequippedBP.AddDynamic(this, &ADGRG_CombatCharacter::CalculateStance);
	m_EquipSlotRightWeapon->m_OnEquippedBP.AddDynamic(this, &ADGRG_CombatCharacter::CalculateStance);
	m_EquipSlotRightWeapon->m_OnUnequippedBP.AddDynamic(this, &ADGRG_CombatCharacter::CalculateStance);

	SetStanceFPtr();
	//
	SetEquipSlotsArray();
}
void ADGRG_CombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentHealth();
}
void ADGRG_CombatCharacter::SetEquipSlotsArray()
{
	m_EquipSlotArray.Reserve(10);
	m_EquipSlotArray.Emplace(m_EquipSlotHead);
	m_EquipSlotArray.Emplace(m_EquipSlotNecklace);
	m_EquipSlotArray.Emplace(m_EquipSlotTorso);
	m_EquipSlotArray.Emplace(m_EquipSlotBelt);
	m_EquipSlotArray.Emplace(m_EquipSlotHand);
	m_EquipSlotArray.Emplace(m_EquipSlotShoe);
	m_EquipSlotArray.Emplace(m_EquipSlotRightRing);
	m_EquipSlotArray.Emplace(m_EquipSlotLeftRing);
	m_EquipSlotArray.Emplace(m_EquipSlotRightWeapon);
	m_EquipSlotArray.Emplace(m_EquipSlotLeftWeapon);
}
void ADGRG_CombatCharacter::SetStanceFPtr()
{
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::EMPTY] = &ADGRG_CombatCharacter::SetStanceAllNull;
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::ONEHAND] = &ADGRG_CombatCharacter::SetStanceNull;
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::DAGGER] = &ADGRG_CombatCharacter::SetStanceNull;
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::SHIELD] = &ADGRG_CombatCharacter::SetStanceNull;
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::TWOHAND] = &ADGRG_CombatCharacter::SetStanceNull;
	m_StanceFPtr[(int)E_EQUIPMENT::EMPTY][(int)E_EQUIPMENT::KATANA] = &ADGRG_CombatCharacter::SetStanceNull;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::ONEHAND][(int)E_EQUIPMENT::ONEHAND] = &ADGRG_CombatCharacter::SetStanceDual;
	m_StanceFPtr[(int)E_EQUIPMENT::DAGGER][(int)E_EQUIPMENT::ONEHAND] = &ADGRG_CombatCharacter::SetStanceDual;
	m_StanceFPtr[(int)E_EQUIPMENT::ONEHAND][(int)E_EQUIPMENT::DAGGER] = &ADGRG_CombatCharacter::SetStanceDual;
	m_StanceFPtr[(int)E_EQUIPMENT::DAGGER][(int)E_EQUIPMENT::DAGGER] = &ADGRG_CombatCharacter::SetStanceDual;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::ONEHAND][(int)E_EQUIPMENT::SHIELD] = &ADGRG_CombatCharacter::SetStanceShield;
	m_StanceFPtr[(int)E_EQUIPMENT::DAGGER][(int)E_EQUIPMENT::SHIELD] = &ADGRG_CombatCharacter::SetStanceShield;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::ONEHAND][(int)E_EQUIPMENT::EMPTY] = &ADGRG_CombatCharacter::SetStanceOneHand;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::DAGGER][(int)E_EQUIPMENT::EMPTY] = &ADGRG_CombatCharacter::SetStanceDagger;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::KATANA][(int)E_EQUIPMENT::EMPTY] = &ADGRG_CombatCharacter::SetStanceKatana;
	//
	m_StanceFPtr[(int)E_EQUIPMENT::TWOHAND][(int)E_EQUIPMENT::EMPTY] = &ADGRG_CombatCharacter::SetStanceTwoHand;
}
void ADGRG_CombatCharacter::SetSlotsSocketName()
{
	m_EquipSlotHead->SetSlotSocketName(FName("S_HEAD"));
	m_EquipSlotTorso->SetSlotSocketName(FName("S_TORSO"));
	m_EquipSlotBelt->SetSlotSocketName(FName("S_BELT"));
	m_EquipSlotShoe->SetSlotSocketName(FName("S_SHOE"));
	m_EquipSlotHand->SetSlotSocketName(FName("S_HAND"));
	m_EquipSlotNecklace->SetSlotSocketName(FName("S_NECK"));
	m_EquipSlotLeftRing->SetSlotSocketName(FName("S_LEFTRING"));
	m_EquipSlotRightRing->SetSlotSocketName(FName("S_RIGHTRING"));
	m_EquipSlotLeftWeapon->SetSlotSocketName(FName("S_LEFTWEAPON"));
	m_EquipSlotRightWeapon->SetSlotSocketName(FName("S_RIGHTWEAPON"));
}
void ADGRG_CombatCharacter::SetSlotsSize()
{
	m_Inventory->SetContainerSize(10, 8);
	m_EquipSlotHead->SetContainerSize(2, 2);
	m_EquipSlotNecklace->SetContainerSize(1, 1);
	m_EquipSlotTorso->SetContainerSize(2, 3);
	m_EquipSlotBelt->SetContainerSize(2, 1);
	m_EquipSlotHand->SetContainerSize(2, 2);
	m_EquipSlotShoe->SetContainerSize(2, 2);
	m_EquipSlotRightRing->SetContainerSize(1, 1);
	m_EquipSlotLeftRing->SetContainerSize(1, 1);
	m_EquipSlotRightWeapon->SetContainerSize(2, 4);
	m_EquipSlotLeftWeapon->SetContainerSize(2, 4);

	m_Inventory->SetContainer();
	m_EquipSlotHead->SetContainer();
	m_EquipSlotTorso->SetContainer();
	m_EquipSlotBelt->SetContainer();
	m_EquipSlotShoe->SetContainer();
	m_EquipSlotHand->SetContainer();
	m_EquipSlotNecklace->SetContainer();
	m_EquipSlotLeftRing->SetContainer();
	m_EquipSlotRightRing->SetContainer();
	m_EquipSlotLeftWeapon->SetContainer();
	m_EquipSlotRightWeapon->SetContainer();
}
void ADGRG_CombatCharacter::SetSlotsEquipableType()
{
	m_EquipSlotHead->SetEquipSlotAble(E_EQUIPMENT::HEAD, true);
	m_EquipSlotNecklace->SetEquipSlotAble(E_EQUIPMENT::NECK, true);
	m_EquipSlotTorso->SetEquipSlotAble(E_EQUIPMENT::TORSO, true);
	m_EquipSlotBelt->SetEquipSlotAble(E_EQUIPMENT::BELT, true);
	m_EquipSlotHand->SetEquipSlotAble(E_EQUIPMENT::GLOVE, true);
	m_EquipSlotShoe->SetEquipSlotAble(E_EQUIPMENT::SHOE, true);
	m_EquipSlotRightRing->SetEquipSlotAble(E_EQUIPMENT::RING, true);
	m_EquipSlotLeftRing->SetEquipSlotAble(E_EQUIPMENT::RING, true);

	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::DAGGER, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::ONEHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, true);

	m_EquipSlotLeftWeapon->SetEquipSlotAble(E_EQUIPMENT::DAGGER, true);
	m_EquipSlotLeftWeapon->SetEquipSlotAble(E_EQUIPMENT::SHIELD, true);
	m_EquipSlotLeftWeapon->SetEquipSlotAble(E_EQUIPMENT::ONEHAND, true);
}
void ADGRG_CombatCharacter::CreateComponents()
{
	m_Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	m_EquipSlotHead = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipHead"));
	m_EquipSlotNecklace = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipNecklace"));
	m_EquipSlotTorso = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipTorso"));
	m_EquipSlotBelt = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipBelt"));
	m_EquipSlotHand = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipHand"));
	m_EquipSlotShoe = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipShoe"));
	m_EquipSlotRightRing = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipRRing"));
	m_EquipSlotLeftRing = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipLRing"));
	m_EquipSlotRightWeapon = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipRWeapon"));
	m_EquipSlotLeftWeapon = CreateDefaultSubobject<UEquipSlot>(TEXT("EquipLWeapon"));
}
void ADGRG_CombatCharacter::CalculateStance()
{
	SetAttackingFalse();

	E_EQUIPMENT LeftHandWeapon = m_EquipSlotLeftWeapon->GetCurrentEquipType();
	E_EQUIPMENT RightHandWeapon = m_EquipSlotRightWeapon->GetCurrentEquipType();
	(this->*m_StanceFPtr[(int)RightHandWeapon][(int)LeftHandWeapon])();
	ChangeStance();
}

void ADGRG_CombatCharacter::ChangeStance()
{
	auto SkeletalMesh = GetMesh();

	SkeletalMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SkeletalMesh->SetAnimInstanceClass(m_AnimSets[(int)m_CurrentStance]);
	auto AnimInst = Cast<UDGRG_HumanCharacter_AnimInstance>(SkeletalMesh->GetAnimInstance());
	SetMaxCombo(AnimInst->m_Motions.Num());
	ResetCombo();
	PRINTF("Current Stance Index: %s", *GETENUMSTRING("E_STANCE",m_CurrentStance));
}


void ADGRG_CombatCharacter::SetStanceAllNull()
{	
	m_EquipSlotLeftWeapon->SetOccupied(false);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, true);
	m_CurrentStance = E_STANCE::EMPTY;
}

void ADGRG_CombatCharacter::SetStanceNull()
{
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, true);
	m_CurrentStance = E_STANCE::EMPTY;
}

void ADGRG_CombatCharacter::SetStanceOneHand()
{
	m_EquipSlotLeftWeapon->SetOccupied(false);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, true);
	m_CurrentStance = E_STANCE::ONEHAND;
}

void ADGRG_CombatCharacter::SetStanceDual()
{
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, false);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, false);
	m_CurrentStance = E_STANCE::DUALWIELD;
}

void ADGRG_CombatCharacter::SetStanceShield()
{
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, false);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, false);
	m_CurrentStance = E_STANCE::SHIELD;
}

void ADGRG_CombatCharacter::SetStanceDagger()
{
	m_EquipSlotLeftWeapon->SetOccupied(false);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::TWOHAND, true);
	m_EquipSlotRightWeapon->SetEquipSlotAble(E_EQUIPMENT::KATANA, true);
	m_CurrentStance = E_STANCE::DAGGER;
}

void ADGRG_CombatCharacter::SetStanceKatana()
{
	m_EquipSlotLeftWeapon->SetOccupied(true);
	m_CurrentStance = E_STANCE::KATANA;
}

void ADGRG_CombatCharacter::SetStanceTwoHand()
{
	m_EquipSlotLeftWeapon->SetOccupied(true);
	m_CurrentStance = E_STANCE::TWOHAND;
}

TArray<UEquipSlot*>& ADGRG_CombatCharacter::GetEquipSlotArray()
{
	return m_EquipSlotArray;
}

bool ADGRG_CombatCharacter::AddItemToEmptySpace( UStoredItem* dItem, FCoord & resultPivot)
{
	bool Result = m_Inventory->AddItemToEmptySpace(dItem, resultPivot);
	if (Result)
	{
		m_OnAddItem.Broadcast(dItem, resultPivot);
	}
	return Result;
}

bool ADGRG_CombatCharacter::AddItemToPivot(FCoord pivot,  UStoredItem * dItem)
{
	bool Result = m_Inventory->AddItemToPivot(pivot, dItem);
	if (Result)
	{
		m_OnAddItem.Broadcast(dItem, pivot);
	}
	return Result;
}

bool ADGRG_CombatCharacter::RemoveItemFromPivot(FCoord pivot,  UStoredItem* dItem)
{
	bool Result = m_Inventory->RemoveItemFromPivot(pivot, dItem);
	if (Result)
	{
		m_OnRemoveItem.Broadcast(dItem, pivot);
	}
	return Result;
}

bool ADGRG_CombatCharacter::RemoveItemFromAuto( UStoredItem* dItem)
{
	bool Result = m_Inventory->RemoveItemFromAuto(dItem);
	if (Result)
	{
		//m_OnRemoveItem.Broadcast(dItem, pivot);
	}
	return Result;
}

bool ADGRG_CombatCharacter::DropItemGround(UStoredItem * dItem)
{
	return m_GameInstance->DropItemGround(GetActorLocation(), dItem);
}

