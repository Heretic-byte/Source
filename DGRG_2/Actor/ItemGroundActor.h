#pragma once
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Widgets/WidgetItemNameCard.h"
#include "Engine/DataTable.h"


#include "ItemGroundActor.generated.h"

class ADGRG_CombatCharacter;
class UInteractable;
class UWidgetComponent;
//class UWidgetItemNameCard;
UCLASS(Abstract)
class DGRG_2_API AItemGroundActor : public AActor
{
	GENERATED_BODY()
	//∂•ø°∂≥±∏¥¬ æ∆¿Ã≈€
public:	
	AItemGroundActor(const FObjectInitializer& ObjectInitializer);
public://events
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact")
	void DropToGround(const FVector& navDestination);
	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void OnOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable, Category = "Interact")
	virtual void AddItemToActor(AActor* interMan);
public:
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetScale(float v);
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetItemMesh(UStaticMesh* meshWant);
	UFUNCTION(BlueprintCallable, Category = "Interact")
	UWidgetItemNameCard * GetWidgetItemNameCard();
protected:
	UFUNCTION(BlueprintCallable, Category = "Curve")
	FVector GetMiddlePoint(FVector startP, FVector destP, float height);
protected:
	virtual void BeginPlay() override;
	virtual void IfManualSet();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	USphereComponent* m_SphereColl; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool m_bInteractWithOverlapped;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool m_bManuallySetID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FDataTableRowHandle m_ManuallyItemID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractable* m_Interactable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UStaticMeshComponent* m_StMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UWidgetComponent* m_WidgetCompo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	TSubclassOf<UWidgetItemNameCard> m_ClassWidgetNameCard;
};
