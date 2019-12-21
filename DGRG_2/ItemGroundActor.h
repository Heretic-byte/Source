// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ItemGroundActor.generated.h"

UCLASS()
class DGRG_2_API AItemGroundActor : public AActor
{
	GENERATED_BODY()
	//∂•ø°∂≥±∏¥¬ æ∆¿Ã≈€
public:	
	// Sets default values for this actor's properties
	AItemGroundActor();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	class ADGRG_CombatCharacter* GetCombatCharacter(AActor* interMan);
	//
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact")
	void DropToGround(const FVector& navDestination);
	UFUNCTION(BlueprintCallable, Category = "Interact")
		void SetScale(float per);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	USphereComponent* m_SphereColl; 
};
