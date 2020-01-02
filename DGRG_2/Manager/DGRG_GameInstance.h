// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
//
#include "Datas/DataTableRowBase.h"
#include "Datas/DGRG_Macro.h"
#include "Datas/DGRG_Enum.h"
#include "Datas/DGRG_Struct.h"
//
#include "DGRG_GameInstance.generated.h"

class AMonsterBase;
class ADGRG_CombatCharacter;
class APlayerCharacter;

class UGoldManager;
class UExpManager;
class UItemManager;
class UPlayerStatManager;
class UOptionManager;
class UDungeonManager;
class UWidgetMasterCanvas;

UCLASS(BlueprintType)
class DGRG_2_API UDGRG_GameInstance : public UGameInstance
{
public:
	//여기서 전부 세이브로드
	GENERATED_BODY()
	
	UDGRG_GameInstance();
#pragma region Managers
protected:
	UPROPERTY(VisibleAnywhere)
	UGoldManager* m_GoldManager;
	UPROPERTY(VisibleAnywhere)
	UExpManager* m_ExpManager;
	UPROPERTY(VisibleAnywhere)
	UItemManager* m_ItemManager;
	UPROPERTY(VisibleAnywhere)
	UPlayerStatManager* m_PlayerStatManager;
	UPROPERTY(VisibleAnywhere)
	UOptionManager* m_OptionManager;
	UPROPERTY(VisibleAnywhere)
	UDungeonManager* m_DgManager;
	UPROPERTY(VisibleAnywhere)
	APlayerCharacter* m_PlayerChar;
	UPROPERTY(VisibleAnywhere)
	UWidgetMasterCanvas* m_MasterCanvas;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGoldManager> m_CGoldManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UExpManager> m_CExpManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UItemManager> m_CItemManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPlayerStatManager> m_CPlayerStatManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOptionManager> m_COptionManager;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDungeonManager> m_CDungeonManager;
#pragma endregion
	//
#pragma region DataTables
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_BaseItemDB;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_MaterialItemDB;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_EquipItemDB;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_HumanStatDB;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_MonsterStatDB;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_ExpTable;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_ItemTierTable;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_DifficultyScaleTable;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_MonsterNamedScaleTable;
	//
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_DungeonSizeLevelScale;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_DungeonSizeDiffyScale;
	//
	UPROPERTY(EditDefaultsOnly)
	UDataTable* m_OptionTable;
#pragma endregion


private:
	const UEnum* m_ItemTierEnumPtr;
	const UEnum* m_DifficultyEnumPtr;
	const UEnum* m_OptionTypeEnumPtr;
public:
#pragma region TableDataGets

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FBaseItemData& GetBaseItemData(FName id) const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FMaterialItemData& GetMaterialItemData(FName id)const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FEquipmentItemData& GetEquipItemData(FName id)const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FMonsterStatTable& GetMonsterStat(FName id)const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FExpTable& GetExpTable(int id)const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FTierScaleStatPerc& GetMonsterNamedScale(E_ITEMTIER itemTier)const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FScaleStatPercTable& GetDifficultyScale(E_DIFFICULTY diff)const;
	UFUNCTION(BlueprintCallable, Category = "Combat")
	const FHumanStatTable& GetHumanStat(FName id)const;
	//
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	const FFloatTable& GetDungeonLevelScale(int level)const;
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	const FFloatTable& GetDungeonDiffyScale(E_DIFFICULTY diff)const;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const FItemTier& GetItemTier(E_ITEMTIER itemTier)const;
	//
	UFUNCTION(BlueprintCallable, Category = "Item")
	const FOptionValueLevelData& GetOptionValue(E_OPTIONTYPE opType)const;
#pragma endregion
	UFUNCTION(BlueprintCallable, Category = "Item")
	APlayerCharacter* GetPlayerCharacter();
	UFUNCTION(BlueprintCallable, Category = "Item")
	UWidgetMasterCanvas* GetMasterCanvas();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetMasterCanvas(UWidgetMasterCanvas* masterCanvas);
public:
	//init
	virtual void Init() override;
	//callback
	UFUNCTION()
	void OnMonsterKilled  ( AMonsterBase* monsterActor) ;
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayerActor(ADGRG_CombatCharacter* combatP);

	bool DropItemGround(FVector origin, UStoredItem * item, float radius = 200.0f);
public:
	UFUNCTION(BlueprintCallable,Category="Manager")
	FORCEINLINE UPlayerStatManager* GetPlayerStatManager() const{return m_PlayerStatManager;} 
	UFUNCTION(BlueprintCallable, Category = "Manager")
	FORCEINLINE UGoldManager* GetGoldManager() const { return m_GoldManager; }
	UFUNCTION(BlueprintCallable, Category = "Manager")
	FORCEINLINE UExpManager* GetExpManager() const { return m_ExpManager; }
	UFUNCTION(BlueprintCallable, Category = "Manager")
	FORCEINLINE UItemManager* GetItemManager() const { return m_ItemManager; }
	UFUNCTION(BlueprintCallable, Category = "Manager")
	FORCEINLINE UOptionManager* GetOptionManager() const { return m_OptionManager; }
	UFUNCTION(BlueprintCallable, Category = "Manager")
	FORCEINLINE UDungeonManager* GetDungeonManager() const { return m_DgManager; }
};
