// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Datas/DGRG_Enum.h"
#include "Components/SceneCaptureComponent2D.h"
//#include 
#include "PortraitRenderActor.generated.h"
class AEquipmentShowActor;
class USpringArmComponent;
class ADGRG_CombatCharacter;
UCLASS()
class DGRG_2_API APortraitRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortraitRenderActor(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere)
	TMap<FName, AActor*> m_MapEquipMeshActors;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* m_SkMeshCompo;
	UPROPERTY(  VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* m_CaptureCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* m_SprintArmCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ADGRG_CombatCharacter* m_CombatChar;
public:	
	void SetSkMesh(USkeletalMesh* skMesh);
	void DestoryEquipActor(FName copiedActorHashName);
	void SetTargetAnimation();
	void SetTargetAnimationDeleWrapper(E_STANCE notUse);
	void AttachEquipMesh(FAttachmentTransformRules& rules,FName socketName,
		AEquipmentShowActor* actorToCopy);
	void SetCamTargetActor(ADGRG_CombatCharacter* targetCharacter);
};
