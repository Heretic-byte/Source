// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGroundActor.h"
#include "Components/WidgetComponent.h"
#include "Interactable.h"


// Sets default values
AItemGroundActor::AItemGroundActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldRoot"));
	m_SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColl"));
	m_SphereColl->SetupAttachment(RootComponent);
	m_SphereColl->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_SphereColl->SetCollisionObjectType(ECC_GameTraceChannel3);
	//FCollisionObjectQueryParams CollObject= FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_GameTraceChannel3));

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
		m_StMesh->SetupAttachment(RootComponent);
	}
	m_ClassWidgetNameCard = UWidgetItemNameCard::StaticClass();
	//
	m_WidgetCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCompo"));
	m_WidgetCompo->SetupAttachment(RootComponent);
	m_WidgetCompo->SetWidgetClass(m_ClassWidgetNameCard);
	m_bManuallySetID = false;
	m_bInteractWithOverlapped = false;
}

UWidgetItemNameCard * AItemGroundActor::GetWidgetItemNameCard()
{
	return Cast<UWidgetItemNameCard>(m_WidgetCompo->GetUserWidgetObject());
}


FVector AItemGroundActor::GetMiddlePoint(FVector startP, FVector destP, float height)
{
	FVector MiddlePoint = destP - startP;
	MiddlePoint += startP;
	MiddlePoint.Z += height;

	return MiddlePoint;
}

void AItemGroundActor::SetScale(float v)
{
	if (v <= 0)
	{
		PRINTF("Scale Can't Be Lessthan 0");
		return;
	}

	SetActorScale3D(FVector(v, v, v));
}

void AItemGroundActor::SetItemMesh(UStaticMesh * meshWant)
{
	m_StMesh->SetStaticMesh(meshWant);
}

void AItemGroundActor::OnOverlapped(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AddItemToActor(OtherActor);
}


void AItemGroundActor::BeginPlay()
{
	

	Super::BeginPlay();
	
	if (m_bInteractWithOverlapped)
	{
		m_SphereColl->OnComponentBeginOverlap.AddDynamic(this, &AItemGroundActor::OnOverlapped);
	}
	m_Interactable->OnInteractBP.AddDynamic(this, &AItemGroundActor::AddItemToActor);
	if (m_bManuallySetID)
	{
		IfManualSet();
	}
}

void AItemGroundActor::IfManualSet()
{//none
}
void AItemGroundActor::AddItemToActor(AActor * interMan)
{//none
}
