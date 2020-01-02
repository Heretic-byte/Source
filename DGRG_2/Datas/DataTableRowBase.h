#pragma once

#include "DGRG_Enum.h"
#include "DGRG_Struct.h"
//
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
//
//#include "Dialogue.h"
#include "Math/Range.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Animation/AnimInstance.h"
#include "UObject/NoExportTypes.h"
//
#include "StoredItem.h"
#include "StoredMaterialItem.h"
#include "StoredEquipItem.h"

#include "DGRG_Macro.h"

#include "DataTableRowBase.generated.h"
class AEquipmentShowActor;
class ADroppedItemActor;
class ADroppedGoldActor;
class ADroppedEquipItem;
class ADroppedMaterialItem;
class UWidgetItemVisual;
//
//class UStoredItem;
//class UStoredEquipItem;
//class UStoredMaterialItem;



UCLASS()
class DGRG_2_API UDataTableRowBase : public UObject
{
	GENERATED_BODY()
	};

USTRUCT(BlueprintType)
struct  FItemTier : public FTableRowBase
{
	//인벤에 들어가는 클래스하나를 만들어주고
	//상속으로 서로 다른 테이블 하나씩 쓰게 만들어줄것
	GENERATED_BODY()

	public:
	FItemTier()
	{
		m_TierName = E_ITEMTIER::NORMAL;
		m_ItemRatio = 1.0f;
		m_SymbolColor = FColor::White;	
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	E_ITEMTIER m_TierName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FColor m_SymbolColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_ItemRatio;
};

USTRUCT(BlueprintType)
struct  FBaseItemData : public FTableRowBase
{
	//인벤에 들어가는 클래스하나를 만들어주고
	//상속으로 서로 다른 테이블 하나씩 쓰게 만들어줄것
	GENERATED_BODY()

	public:
	FBaseItemData()
	{
		m_Name = FText::FromString("NameNotSet");
		m_Description = FText::FromString("BaseItemData");
		m_nValue = 10;
		m_WidthHeight.nX = 2;
		m_WidthHeight.nY = 3;
		m_nMaxStack = 999;
		m_Stackable = true;
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	E_ITEMTYPE m_ItemType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText m_Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 m_nValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* m_Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* m_DropStMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText m_Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCoord m_WidthHeight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 m_nMaxStack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool m_Stackable;
};

USTRUCT(BlueprintType)
struct  FMaterialItemData : public FBaseItemData
{
	GENERATED_BODY()

	public:
	FMaterialItemData()
	{
		m_Description = FText::FromString("Material Item");
		m_nValue = 10;
		m_WidthHeight.nX = 2;
		m_WidthHeight.nY = 2;
		m_nMaxStack = 999;
		m_Stackable = true;
	}
};




USTRUCT(BlueprintType)
struct  FEquipmentItemData : public FBaseItemData
{
	GENERATED_BODY()

	public:
	FEquipmentItemData()
	{
		m_Description = FText::FromString("Equipment Item");
		m_nValue = 10;
		m_WidthHeight.nX = 2;
		m_WidthHeight.nY = 3;
		m_Scale = 1.0f;
		m_EquipmentRatio = 1.0f;
		m_Stackable = false;
		//
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float m_EquipmentRatio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AEquipmentShowActor> m_ItemEquipMesh;//장착할수있는 액터로 변경필요
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	E_EQUIPMENT m_EquipmentType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_Scale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<E_OPTIONTYPE> m_Options;
};

USTRUCT(BlueprintType)//난이도
struct FScaleStatPercTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScaleStatPercTable()
	{
		m_HpScale = 1.f;
		m_DmgScale = 1.f;
		m_AmScale = 1.f;
		m_FmScale = 1.f;
		m_EmScale = 1.f;
		m_SmScale = 1.f;
		m_ExpScale = 1.f;
		m_DropRateScale = 1.f;
		m_GoldBonusScale = 1.f;
	}
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_HpScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_DmgScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_AmScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_FmScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_EmScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_SmScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_ExpScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_DropRateScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_GoldBonusScale;
protected:
	static const  FTextFormat FormatToText;
public:
	FORCEINLINE FText ToTextDiffyMonster() const
	{
		FFormatOrderedArguments Args;
		Args.Add(m_HpScale*100.f);
		Args.Add(m_DmgScale*100.f);
		Args.Add(m_ExpScale*100.f);
		Args.Add(m_DropRateScale*100.f);
		Args.Add(m_GoldBonusScale*100.f);
		
		return FText::Format(FormatToText, Args);
	}
};

USTRUCT(BlueprintType)//티어
struct FTierScaleStatPerc : public FScaleStatPercTable
{
	GENERATED_BODY()

public:
	FTierScaleStatPerc()
	{
		m_AsScale = 1.f;
		m_MsScale = 1.f;
		m_SizeScale = 1.f;
	}
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_AsScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_MsScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_SizeScale;
};


USTRUCT(BlueprintType)
struct  FMonsterStatTable : public FTableRowBase
{
public:
	GENERATED_BODY()
	FMonsterStatTable()
	{
		m_MonsterName = FText::FromString("Set Name");
		m_EarnExp = 1;
		m_DropGoldAmount = 100;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText m_MonsterName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScaleStatPercTable m_MonsterStatsScaleConst;//이거 곱하기 레벨
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItemTierRollRatio m_ItemTierRoll;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_EarnExp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_DropGoldAmount;//이값의 3할쁠마
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDropItemData> m_DropItemDatas;
public:
	FORCEINLINE void CalculateScale(FStatDefault& outerModifyStat,int level, 
		const FScaleStatPercTable& tier, const FScaleStatPercTable& diff) const
	{
		SetStatDefaultValue(outerModifyStat, level);
		SetStatPercBonus(outerModifyStat, tier);
		SetStatPercBonus(outerModifyStat, diff);
	}
	void SetStatPercBonus(FStatDefault & outerModifyStat, const FScaleStatPercTable & tier) const
	{
		outerModifyStat.m_HealthPoint.IncreasePerBonus(tier.m_HpScale);
		outerModifyStat.m_AttackDamage.IncreasePerBonus(tier.m_DmgScale);
		outerModifyStat.m_Armour.IncreasePerBonus(tier.m_AmScale);
		outerModifyStat.m_FireArmour.IncreasePerBonus(tier.m_FmScale);
		outerModifyStat.m_ElectricArmour.IncreasePerBonus(tier.m_EmScale);
		outerModifyStat.m_SoulArmour.IncreasePerBonus(tier.m_SmScale);
		outerModifyStat.m_GoldBonusScale.IncreasePerBonus(tier.m_GoldBonusScale);
		outerModifyStat.m_ExpScale.IncreasePerBonus(tier.m_ExpScale);
	}
	void SetStatDefaultValue(FStatDefault & outerModifyStat, int level) const
	{
		outerModifyStat.m_HealthPoint.SetValue(m_MonsterStatsScaleConst.m_HpScale*level);
		outerModifyStat.m_AttackDamage.SetValue(m_MonsterStatsScaleConst.m_DmgScale*level);
		outerModifyStat.m_Armour.SetValue(m_MonsterStatsScaleConst.m_AmScale*level);
		outerModifyStat.m_FireArmour.SetValue(m_MonsterStatsScaleConst.m_FmScale*level);
		outerModifyStat.m_ElectricArmour.SetValue(m_MonsterStatsScaleConst.m_EmScale*level);
		outerModifyStat.m_SoulArmour.SetValue(m_MonsterStatsScaleConst.m_SmScale*level);
		outerModifyStat.m_GoldBonusScale.SetValue(m_MonsterStatsScaleConst.m_GoldBonusScale*level);
		outerModifyStat.m_ExpScale.SetValue(m_MonsterStatsScaleConst.m_ExpScale*level);
	}
};




USTRUCT(BlueprintType)//난이도,티어
struct FHumanStatTable : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FHumanStatTable()
	{

	}
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatDefault m_StatDefault;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatChar m_StatChar;
};


USTRUCT(BlueprintType)
struct  FExpTable : public FTableRowBase
{
public:
	GENERATED_BODY()
	FExpTable()
	{
		m_ExpNeed = 1000;
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int m_ExpNeed;
};



USTRUCT(BlueprintType)
struct  FFloatTable : public FTableRowBase
{
	//인벤에 들어가는 클래스하나를 만들어주고
	//상속으로 서로 다른 테이블 하나씩 쓰게 만들어줄것
	GENERATED_BODY()

	public:
	FFloatTable()
	{
		m_Value = 1.0f;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_Value;

};


USTRUCT(BlueprintType)
struct  FOptionValueLevelData : public FTableRowBase
{
	GENERATED_BODY()
		//ID = E_OPTIONTYPE
public:
	FOptionValueLevelData()
	{
		m_OptionValue.Init(FOptionValue(),(int)E_GLOBAL_CONST::MAXLEVEL);
		m_IsPercValue = false;
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FOptionValue> m_OptionValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText m_OptionName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool m_IsPercValue;
};