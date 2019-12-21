// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStorageActor.h"

// Sets default values
AItemStorageActor::AItemStorageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("StorageHoldRoot"));


	m_ItemContainer = CreateDefaultSubobject<UItemContainer>(TEXT("ItemContain"));

	m_InteractCompo = CreateDefaultSubobject<UInteractable>(TEXT("Interactable"));

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshRender"));
	m_Mesh->SetupAttachment(RootComponent);

}

