// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemContainer.h"
#include "Inventory.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class  UInventory : public UItemContainer
{
public:
	GENERATED_BODY()
	UInventory();


};