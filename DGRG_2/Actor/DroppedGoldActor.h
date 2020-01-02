// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemGroundActor.h"
#include "DroppedGoldActor.generated.h"
//#include "GoldGroundActor.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API ADroppedGoldActor : public AItemGroundActor
{
	//°ñµå´Â ±×³É ¸ö¿¡´êÀ¸¸é ¸Ô¾îÁü
	GENERATED_BODY()
public:
	ADroppedGoldActor(const FObjectInitializer& ObjectInitializer);
	//
	void SetGoldAmount(int goldV);
	virtual void  AddItemToActor(AActor* interMan) override;
	virtual void  IfManualSet() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int m_nGoldAmount;
	FTextFormat m_GoldFormat;
};
