// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGRG_DungeonThemeAsset.h"

#include "MonsterBase.h"
#include "Components/SphereComponent.h"
#include "MonsterHordeManager.generated.h"

class ADGRG_Dungeon;

UCLASS()
class DGRG_2_API AMonsterHordeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterHordeManager();

	void SpawnHorde( ADGRG_Dungeon* const dg);
	UFUNCTION(BlueprintCallable,Category="Dungeon")
	void SetActiveTrueAll();
	//콜라이더 붙일것
	//범위 맞춰줄것

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<AMonsterBase*> m_MyMonsters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	USphereComponent* m_SphereColl;
};
