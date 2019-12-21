#pragma once

#include "DGRG_CombatCharacter.h"
#include "Interactable.h"
#include "MonsterBase.h"
#include "PlayerCharacter.generated.h"

//class AMonsterBase;

UCLASS()
class DGRG_2_API APlayerCharacter : public ADGRG_CombatCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APlayerCharacter();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInteractable* m_InteractObj;
	void SetNullInteract();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void CheckInteractable();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void CheckTargetMonster();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	bool InteractWithTarget();
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFoundInteractBP;
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFailFoundInteractBP;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	AMonsterBase::FVoidMonsterBP OnFoundMonsterBP;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	AMonsterBase::FVoidMonsterBP OnFoundEndMonsterBP;
protected:
	UPROPERTY(VisibleAnywhere)
	AMonsterBase* m_CurrentAttackTarget;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> m_MonsterCastIgnore;

	FVector m_MonsterCastHalfSizeWant;
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetNullAttackTarget();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackTarget(AMonsterBase* target);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	AMonsterBase* GetAttackTarget();

	virtual bool TryAttack() override;

	virtual void GetKill() override;
protected:
	void SetRenderFocusOn(AActor* target);
	void SetRenderFocusOff(AActor* target);
};
