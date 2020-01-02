// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "EquipmentShowActor.generated.h"

UCLASS()
class DGRG_2_API AEquipmentShowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentShowActor();
protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;
public:
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetScale(float scale);
};
