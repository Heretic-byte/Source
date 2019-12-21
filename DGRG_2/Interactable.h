// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "Components/ActorComponent.h"
#include "Interactable.generated.h"

class ADGRG_BaseCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class  UInteractable :   public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UInteractable();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void Interact(AActor* interMan);

	UPROPERTY(BlueprintAssignable, Category = "Interact")
	ADGRG_BaseCharacter::FVoidActorBP OnInteractBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_Unlocked;

	UPROPERTY(BlueprintAssignable, Category = "Interact")
	ADGRG_BaseCharacter::FVoidActorBP OnCantInteractBP;

	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnLockedBP;
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnUnlockedBP;

	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFocusInBP;

	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFocusOutBP;

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetLock();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetUnlock();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetFocusIn();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetFocusOut();
};
