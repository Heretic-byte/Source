// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedItemActor.h"
#include "Item.h"
#include "Interactable.h"
#include "DGRG_CombatCharacter.h"
#include "StoredItem.h"
#include "DGRG_Struct.h"
#include "DGRG_GameInstance.h"
#include "WidgetItemNameCard.h"
#include "ItemManager.h"

ADroppedItemActor::ADroppedItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	m_Interactable = CreateDefaultSubobject<UInteractable>(TEXT("InterCompo"));
	m_StMesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("SkMeshCompo"));
	if (m_StMesh)
	{
		m_StMesh->AlwaysLoadOnClient = true;
		m_StMesh->AlwaysLoadOnServer = true;
		m_StMesh->bOwnerNoSee = false;
		m_StMesh->bCastDynamicShadow = false;
		m_StMesh->bAffectDynamicIndirectLighting = false;
		m_StMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;


		m_StMesh->SetupAttachment(RootComponent);
		static FName MeshCollisionProfileName(TEXT("EquipMesh2"));
		m_StMesh->SetCollisionProfileName(MeshCollisionProfileName);
		m_StMesh->SetGenerateOverlapEvents(false);
		m_StMesh->SetCanEverAffectNavigation(false);
		//
		m_StMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	m_ClassWidgetNameCard = UWidgetItemNameCard::StaticClass();
	//
	m_WidgetCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCompo"));
	m_WidgetCompo->SetupAttachment(RootComponent);
	m_WidgetCompo->SetWidgetClass(m_ClassWidgetNameCard);
	m_ManuallySetID = false;
	m_CurrentItemInstance = nullptr;
}

void ADroppedItemActor::BeginPlay()
{
	Super::BeginPlay();
	m_Interactable->OnInteractBP.AddDynamic(this,&ADroppedItemActor::AddItemToActor);

	if (m_ManuallySetID)
	{
		FBaseItemData* FoundItem = m_ManuallyItemID.GetRow<FBaseItemData>("");
		auto* MyGameInstance = GetGameInstance<UDGRG_GameInstance>();
		auto* ItemInstance=MyGameInstance->GetItemManager()->CreateItemInstance(*FoundItem);
		SetItemData(ItemInstance);
	}
}

void ADroppedItemActor::AddItemToActor(AActor* interMan)
{
	auto InterChar = GetCombatCharacter(interMan);

	if (!InterChar)
	{
		return;
	}
	FCoord NotUse;
	if (InterChar->AddItemToEmptySpace(m_CurrentItemInstance, NotUse))
	{
		Destroy();
	}
}


FVector ADroppedItemActor::GetMiddlePoint(FVector  startP, FVector  destP, float height)
{
	FVector MiddlePoint = destP - startP;
	MiddlePoint += startP;
	MiddlePoint.Z += height;

	return MiddlePoint;
}

void ADroppedItemActor::SetItemData(UStoredItem* itemData) 
{
	m_CurrentItemInstance = itemData;
	m_StMesh->SetStaticMesh(m_CurrentItemInstance->GetItemData().m_DropStMesh);
	Cast<UWidgetItemNameCard>(m_WidgetCompo->GetUserWidgetObject())->SetItemName(itemData);
}
