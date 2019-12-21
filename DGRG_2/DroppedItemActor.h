// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemGroundActor.h"
//#include "StoredItem.h"
#include "DGRG_Enum.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MonsterBase.h"

#include "DroppedItemActor.generated.h"

/**
 * 루트 컴포넌트 읹
 */
class UInteractable;
class UItem;
class UStoredItem;
class UWidgetItemNameCard;
struct FStatDefault;


UCLASS()
class DGRG_2_API ADroppedItemActor : public AItemGroundActor
{
	GENERATED_BODY()
		//
public:
		ADroppedItemActor();
protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
		UInteractable* m_Interactable;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
		UStaticMeshComponent* m_StMesh;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
		UWidgetComponent* m_WidgetCompo;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
		bool m_ManuallySetID;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
		FDataTableRowHandle m_ManuallyItemID;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		UStoredItem* m_CurrentItemInstance;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
		TSubclassOf<UWidgetItemNameCard> m_ClassWidgetNameCard;
public:
		UFUNCTION(BlueprintCallable,Category = "Item")
		virtual void SetItemData( UStoredItem* itemData);
		//set name
		//set color
		//set mesh
protected:
		virtual void BeginPlay() override;
		UFUNCTION()
		void AddItemToActor(AActor* interMan);
		

		UFUNCTION(BlueprintCallable, Category = "Curve")
		FVector GetMiddlePoint(FVector startP,FVector destP,float height);
};
