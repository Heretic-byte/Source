// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
//#include "DGRG_2GameMode.h"
#include "Item.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class  UItem : public UActorComponent
{
	GENERATED_BODY()

public:
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle m_ItemID;

	//상속으로 다르게
};

