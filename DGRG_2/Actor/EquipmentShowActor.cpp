// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentShowActor.h"
// Sets default values
AEquipmentShowActor::AEquipmentShowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldRoot"));
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("EquipMesh0"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = false;
		Mesh->bAffectDynamicIndirectLighting = false;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		//RootComponent = Mesh;
		Mesh->SetupAttachment(RootComponent);
		static FName MeshCollisionProfileName(TEXT("EquipMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
		Mesh->bUseAsOccluder = false;

	}

}

void AEquipmentShowActor::SetScale(float scale)
{
	Mesh->SetWorldScale3D(FVector(scale, scale, scale));
}
