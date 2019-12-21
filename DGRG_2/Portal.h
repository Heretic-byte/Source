// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class DGRG_2_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UWorld>> m_WorldWantOpen;
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void OpenLevel(int index);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void LoadLevel(int index, bool visible);
};
