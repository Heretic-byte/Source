#pragma once

#include "DGRG_CombatCharacter.h"
#include "Interactable.h"
#include "MonsterBase.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APortraitRenderActor;
class UInputComponent;

UCLASS()
class DGRG_2_API APlayerCharacter : public ADGRG_CombatCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFoundInteractBP;
	UPROPERTY(BlueprintAssignable, Category = "Interact")
	FVoidVoidBP OnFailFoundInteractBP;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	AMonsterBase::FVoidMonsterBP OnFoundMonsterBP;
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	AMonsterBase::FVoidMonsterBP OnFoundEndMonsterBP;
public:
	FORCEINLINE  USpringArmComponent* GetCameraBoom() const { return m_CameraBoom; }
	FORCEINLINE  UCameraComponent* GetFollowCamera() const { return m_FollowCamera; }
	virtual bool TryAttack() override;
	virtual void GetKill() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void TryCheckInteractable();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void TryCheckTargetMonster();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	bool InteractWithTarget();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetNullAttackTarget();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAttackTarget(AMonsterBase* target);
	UFUNCTION(BlueprintCallable, Category = "Combat")
	AMonsterBase* GetAttackTarget();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APortraitRenderActor* m_PortraitActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInteractable* m_InteractObj;
	UPROPERTY(VisibleAnywhere)
	AMonsterBase* m_CurrentAttackTarget;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> m_MonsterCastIgnore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APortraitRenderActor> m_ClassPortRender;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector m_PortActorPosition;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_PortActorZRot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector m_MonsterCastHalfSizeWant;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void SetPortraitActor();
	void MoveForward(float Value);
	void MoveRight(float Value);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void SetNullInteract();
	void SetRenderFocusOn(AActor* target);
	void SetRenderFocusOff(AActor* target);
};
