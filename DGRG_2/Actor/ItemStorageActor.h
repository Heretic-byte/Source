// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "ItemContainer.h"

#include "Interactable.h"
#include "ItemStorageActor.generated.h"

UCLASS()
class DGRG_2_API AItemStorageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemStorageActor();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UItemContainer* m_ItemContainer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInteractable* m_InteractCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* m_Mesh;

};
