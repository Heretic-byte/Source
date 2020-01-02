// Fill out your copyright notice in the Description page of Project Settings.


#include "PortraitRenderActor.h"
#include "EquipmentShowActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "DGRG_CombatCharacter.h"

// Sets default values
APortraitRenderActor::APortraitRenderActor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	m_MapEquipMeshActors.Empty();
	m_MapEquipMeshActors.Reserve(12);
	SetTickableWhenPaused(true);
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	m_SkMeshCompo = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_SkMeshCompo->bCastDynamicShadow = false;
	m_SkMeshCompo->SetupAttachment(RootComponent);
	m_SprintArmCompo = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_SprintArmCompo->SetupAttachment(RootComponent);
	m_CaptureCompo = CreateOptionalDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	m_CaptureCompo->FOVAngle = 50.f;
	m_CaptureCompo->SetupAttachment(m_SprintArmCompo);
	//m_CaptureCompo->ShowOnlyComponent(m_SkMeshCompo);
}

void APortraitRenderActor::SetSkMesh(USkeletalMesh * skMesh)
{
	m_SkMeshCompo->SetSkeletalMesh(skMesh);
}

void APortraitRenderActor::DestoryEquipActor(FName copiedActorHashName)
{
	m_MapEquipMeshActors[copiedActorHashName]->Destroy();
}


void APortraitRenderActor::SetTargetAnimation()
{
	m_SkMeshCompo->SetAnimInstanceClass(m_CombatChar->GetAnimBP()->GetClass());
}

void APortraitRenderActor::SetTargetAnimationDeleWrapper(E_STANCE notUse)
{
	SetTargetAnimation();
}

void APortraitRenderActor::AttachEquipMesh(FAttachmentTransformRules & rules, FName socketName, AEquipmentShowActor * actorToCopy)
{
	FActorSpawnParameters ActorSpawnP;
	ActorSpawnP.Template = actorToCopy;
	auto* CreatedItemActor = GetWorld()->SpawnActor(actorToCopy->GetClass(), &m_SkMeshCompo->GetComponentTransform(), ActorSpawnP);
	auto* CreatedItemCopy = Cast<AEquipmentShowActor>(CreatedItemActor);
	CreatedItemCopy->AttachToComponent(m_SkMeshCompo, rules, socketName);
	m_MapEquipMeshActors.Add(actorToCopy->GetFName(), CreatedItemCopy);
	m_CaptureCompo->ShowOnlyActorComponents(CreatedItemCopy);
}

void APortraitRenderActor::SetCamTargetActor(ADGRG_CombatCharacter * targetCharacter)
{
	m_CombatChar = targetCharacter;
}
