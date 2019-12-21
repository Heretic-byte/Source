// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Animation/AnimInstance.h"
#include "DGRG_HumanCharacter_AnimInstance.generated.h"

/**
 * 
 */

class ADGRG_BaseCharacter;
UCLASS()
class DGRG_2_API UDGRG_HumanCharacter_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UDGRG_HumanCharacter_AnimInstance()
	{
		m_IsHitten = false;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAnimMontage*> m_Motions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* m_DeathMotion;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_MoveLength;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetMoveVector();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetHitten();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	ADGRG_BaseCharacter* GetOwner();

	UPROPERTY(BlueprintReadWrite)
	bool m_IsHitten;
};
