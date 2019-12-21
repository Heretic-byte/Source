// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_Macro.h"
#include "DGRG_BaseCharacter.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"




UCLASS()
class DGRG_2_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATargetPoint* m_DestPoint;
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OpenDoorToMove(ADGRG_BaseCharacter* character);
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	ADGRG_BaseCharacter::FCharDelegate OnEnterDoor;
	
};
