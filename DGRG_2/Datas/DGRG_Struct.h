// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "DGRG_Macro.h"
#include "DGRG_Enum.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DGRG_Struct.generated.h"
#define MAXSTAT 999999999999999999999999.f
/**
 *
 */
UCLASS()
class DGRG_2_API UDGRG_Struct : public UObject
{
	GENERATED_BODY()

};



USTRUCT(BlueprintType)
struct FCoord
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 nX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 nY;

	FCoord() :
		nX(0),
		nY(0)
	{
	}

	FCoord(int x, int y) :
		nX(x),
		nY(y)
	{
	}

	bool operator==(const FCoord& right)const
	{
		return nX == right.nX&&nY == right.nY;
	}
	FCoord operator+(const FCoord& right)const
	{
		return FCoord(nX + right.nX, nY + right.nY);
	}
	FCoord operator-(const FCoord& right)const
	{
		return FCoord(nX - right.nX, nY - right.nY);
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("%dx%d"), nX, nY);
	}
};

USTRUCT(BlueprintType)
struct FStatF
{
	GENERATED_BODY()

public:
	FStatF():
		m_fStatMaximumLimit(MAXSTAT),
		m_fValue(1.f),
		m_fAbsBonusValue(0.f),
		m_fPerBonusValue(1.f),
		m_fFinalValue(m_fValue)

	{

	}
	FStatF(int v):
		m_fStatMaximumLimit(MAXSTAT),
		m_fValue(v),
		m_fAbsBonusValue(0.f),
		m_fPerBonusValue(1.f),
		m_fFinalValue(m_fValue)
	{
		
	}
	FStatF(float v):
		m_fStatMaximumLimit(MAXSTAT),
		m_fValue (v),
		m_fAbsBonusValue ( 0.f),
		m_fPerBonusValue (1.f),
		m_fFinalValue (m_fValue)
	{
		
	}
public:
	static const  FText UnitSymbol[9];
private:
	UPROPERTY(EditDefaultsOnly)
	float m_fStatMaximumLimit;
	UPROPERTY(EditDefaultsOnly)
	float m_fValue;
	float m_fAbsBonusValue;
	float m_fPerBonusValue;
public:
	UPROPERTY(BlueprintReadOnly)
	float m_fFinalValue;
private:
	FORCEINLINE void CalculateValue()
	{
		m_fFinalValue = m_fPerBonusValue * (m_fValue + m_fAbsBonusValue);

		

		if (m_fFinalValue < 0)
		{
			m_fFinalValue = 0;
		}

		if (m_fFinalValue > m_fStatMaximumLimit)
		{
			m_fFinalValue = m_fStatMaximumLimit;
		}
	}
public:
	FORCEINLINE float GetDefaultValue() const
	{
		return m_fValue;
	}
	FORCEINLINE float GetAbsBonusValue() const
	{
		return m_fAbsBonusValue;
	}
	FORCEINLINE float GetPerBonusValue() const
	{
		return m_fPerBonusValue;
	}
	FORCEINLINE float GetFinalValue() const
	{
		return m_fFinalValue;
	}
	FORCEINLINE float GetOnlyBonusValue() const
	{
		return m_fFinalValue- GetDefaultValue();
	}

	FORCEINLINE void SetMaxLimit(float v)
	{
		m_fStatMaximumLimit = v;
		CalculateValue();
	}

	FORCEINLINE void SetValue(float v)
	{
		m_fValue = v;
		CalculateValue();
	}
	FORCEINLINE void SetValue(int v)
	{
		m_fValue = v;
		CalculateValue();
	}
	FORCEINLINE void SetValueFromFinal(const FStatF& v)
	{
		m_fValue = v.GetFinalValue();
		CalculateValue();
	}
	FORCEINLINE void SetValueFromDefault(const FStatF& v)
	{
		m_fValue = v.GetDefaultValue();
		CalculateValue();
	}
	//
	FORCEINLINE void IncreaseDefaultValue(float v)
	{
		m_fValue += v;
		CalculateValue();
	}
	FORCEINLINE void DecreaseDefaultValue(float v)
	{
		m_fValue -= v;
		if (m_fValue < 0.f)
		{
			m_fValue = 0.f;
		}
		CalculateValue();
	}
	FORCEINLINE void IncreasePerBonus(float v)
	{
		m_fPerBonusValue += v;
		CalculateValue();
	}
	FORCEINLINE void DecreasePerBonus(float v)
	{
		m_fPerBonusValue -= v;
		CalculateValue();
	}
	FORCEINLINE void IncreaseAbsBonus(float v)
	{
		m_fAbsBonusValue += v;
		CalculateValue();
	}
	FORCEINLINE void DecreaseAbsBonus(float v)
	{
		m_fAbsBonusValue -= v;

		CalculateValue();
	}
	//
	FORCEINLINE void IncreasePerBonus(int v)
	{
		m_fPerBonusValue += v;
		CalculateValue();
	}
	FORCEINLINE void DecreasePerBonus(int v)
	{
		m_fPerBonusValue -= v;
		CalculateValue();
	}
	FORCEINLINE void IncreaseAbsBonus(int v)
	{
		m_fAbsBonusValue += v;
		CalculateValue();
	}
	FORCEINLINE void DecreaseAbsBonus(int v)
	{
		m_fAbsBonusValue -= v;
		CalculateValue();
	}

	FORCEINLINE void ClearBonus()
	{
		m_fAbsBonusValue = 0.f;
		m_fPerBonusValue = 1.f;
	}
	FORCEINLINE FText GetFloatAsStringWithPrecision(float TheFloat, int32 Precision, bool IncludeLeadingZero = true) const
	{
		float Rounded = roundf(TheFloat);
		if (FMath::Abs(TheFloat - Rounded) < FMath::Pow(10, -1 * Precision))
		{
			TheFloat = Rounded;
		}
		FNumberFormattingOptions NumberFormat;					//Text.h
		NumberFormat.MinimumIntegralDigits = (IncludeLeadingZero) ? 1 : 0;
		NumberFormat.MaximumIntegralDigits = 10000;
		NumberFormat.MinimumFractionalDigits = Precision;
		NumberFormat.MaximumFractionalDigits = Precision;
		return FText::AsNumber(TheFloat, &NumberFormat);
	}

#pragma region Operator
	//

	FORCEINLINE FStatF& operator++()
	{
		m_fValue++;
		CalculateValue();
		return *this;
	}

	FORCEINLINE FStatF operator++(int)
	{
		FStatF Temp = *this;
		++*this;

		return Temp;
	}
	
	FORCEINLINE FStatF& operator--()
	{
		m_fValue--;
		CalculateValue();
		return *this;
	}

	FORCEINLINE FStatF operator--(int)
	{
		FStatF Temp = *this;
		--*this;

		return Temp;
	}



	FText ToText(int floatCount=1) const//its heavy
	{
		float Cache = this->GetFinalValue();
		float Thous = (int)E_GLOBAL_CONST::THOUS;
		float Mile=(int)E_GLOBAL_CONST::MILE;
		int Count=0;

		while (Cache> Thous)//Mile
		{
			Cache /= Thous;
			Count++;
		}
		auto ValueText= GetFloatAsStringWithPrecision(Cache, floatCount);
		FFormatOrderedArguments Args;
		Args.Add(ValueText);
		Args.Add(UnitSymbol[Count]);

		auto FormatT = FTextFormat(FText::FromString("{0}{1}"));
		return FText::Format(FormatT, Args);
	}
	FText ToTextPerc(int floatCount = 1) const//its heavy
	{
		float Cache = this->GetFinalValue();
		float Thous = (int)E_GLOBAL_CONST::THOUS;
		float Mile = (int)E_GLOBAL_CONST::MILE;
		int Count = 0;

		while (Cache > Mile)
		{
			Cache /= Thous;
			Count++;
		}
		//현재값이 1 기준으로
		Cache *= 100.f;
		auto ValueText = GetFloatAsStringWithPrecision(Cache, floatCount);
		FFormatOrderedArguments Args;
		Args.Add(ValueText);
		Args.Add(UnitSymbol[Count]);

		auto FormatT = FTextFormat(FText::FromString("{0}{1}%"));
		return FText::Format(FormatT, Args);
	}
#pragma endregion
};


USTRUCT(BlueprintType)
struct FStatChar
{
	GENERATED_BODY()
	public:

	FStatChar()
	{
		m_Str.SetValue(1);
		m_Agil.SetValue(1);
		m_Luck.SetValue(1);
	}
	FStatChar(int s, int a, int l) :
		m_Str(s),
		m_Agil(a),
		m_Luck(l)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_Str;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_Agil;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_Luck;
public:
	FORCEINLINE void SetStatFromDefault(const FStatChar& Other)
	{
		this->m_Str.SetValueFromDefault(Other.m_Str);
		this->m_Agil.SetValueFromDefault(Other.m_Agil);
		this->m_Luck.SetValueFromDefault(Other.m_Luck);
	}
};
//몬스터도 가지고 있고 사람도 가지고 있는것
//고로 수치 스텟
USTRUCT(BlueprintType)
struct FStatDefault
{
	//GENERATED_USTRUCT_BODY()
	GENERATED_BODY()

public:
	FStatDefault()
	{

	}
	
	FStatDefault(const FStatDefault& copy)
	{
		m_HealthPoint.SetValueFromDefault(copy.m_HealthPoint);
		m_AttackSpeed.SetValueFromDefault(copy.m_AttackSpeed);
		m_MovementSpeed.SetValueFromDefault(copy.m_MovementSpeed);
		m_AttackDamage.SetValueFromDefault(copy.m_AttackDamage);
		m_Armour.SetValueFromDefault(copy.m_Armour);
		m_FireArmour.SetValueFromDefault(copy.m_FireArmour);
		m_ElectricArmour.SetValueFromDefault(copy.m_ElectricArmour);
		m_SoulArmour.SetValueFromDefault(copy.m_SoulArmour);
		m_ExpScale.SetValueFromDefault(copy.m_ExpScale);
		m_DropRateScale.SetValueFromDefault(copy.m_DropRateScale);
		m_GoldBonusScale.SetValueFromDefault(copy.m_GoldBonusScale);
	}
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_HealthPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_AttackSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_MovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_AttackDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_Armour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_FireArmour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_ElectricArmour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_SoulArmour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_ExpScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_DropRateScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FStatF m_GoldBonusScale;

	FORCEINLINE FString ToString() const
	{
		return FString::
			Printf(TEXT(
				"HP: %3.3f \n AS: %.2f \n MS : %.2f \n AD : %.2f \n AM : %.2f \n FAM : %.2f \n EAM : %.2f \n SAM : %.2f \n EXPS : %.2f \n DRPS : %.2f \n GBS : %.2f \n SS : %.2f \n"));
	}//

	FORCEINLINE void SetStatFromDefault(const FStatDefault& Other)
	{
		this->m_Armour.SetValueFromDefault (Other.m_Armour);
		this->m_AttackDamage.SetValueFromDefault(Other.m_AttackDamage);
		this->m_AttackSpeed.SetValueFromDefault(Other.m_AttackSpeed);
		this->m_DropRateScale.SetValueFromDefault (Other.m_DropRateScale);
		this->m_ElectricArmour.SetValueFromDefault(Other.m_ElectricArmour);
		this->m_ExpScale.SetValueFromDefault(Other.m_ExpScale);
		this->m_FireArmour.SetValueFromDefault(Other.m_FireArmour);
		this->m_GoldBonusScale.SetValueFromDefault(Other.m_GoldBonusScale);
		this->m_HealthPoint.SetValueFromDefault(Other.m_HealthPoint);
		this->m_MovementSpeed.SetValueFromDefault(Other.m_MovementSpeed);
		this->m_SoulArmour.SetValueFromDefault(Other.m_SoulArmour);
	}

	FORCEINLINE void SetStatFromFinal(const FStatDefault& Other)
	{
		this->m_Armour.SetValueFromFinal(Other.m_Armour);
		this->m_AttackDamage.SetValueFromFinal(Other.m_AttackDamage);
		this->m_AttackSpeed.SetValueFromFinal(Other.m_AttackSpeed);
		this->m_DropRateScale.SetValueFromFinal(Other.m_DropRateScale);
		this->m_ElectricArmour.SetValueFromFinal(Other.m_ElectricArmour);
		this->m_ExpScale.SetValueFromFinal(Other.m_ExpScale);
		this->m_FireArmour.SetValueFromFinal(Other.m_FireArmour);
		this->m_GoldBonusScale.SetValueFromFinal(Other.m_GoldBonusScale);
		this->m_HealthPoint.SetValueFromFinal(Other.m_HealthPoint);
		this->m_MovementSpeed.SetValueFromFinal(Other.m_MovementSpeed);
		this->m_SoulArmour.SetValueFromFinal(Other.m_SoulArmour);
	}
	

};


USTRUCT(BlueprintType)
struct FQuality
{
	GENERATED_BODY()
public:
	FQuality()
	{
		m_MinQuality = -0.2f;
		m_MaxQuality = 0.2f;
		m_CurrentQuality = 1.0f;
	}
	FQuality(float min, float max)
	{
		m_MinQuality = min;
		m_MaxQuality = max;
		m_CurrentQuality = 1.0f;
	}
public://ClampMin="N"
		float m_MinQuality;
		float m_MaxQuality;

	float m_CurrentQuality;

	FORCEINLINE float SetQualityRandom()
	{
		m_CurrentQuality = FMath::RandRange(m_MinQuality, m_MaxQuality);
		return m_CurrentQuality;
	}
};

USTRUCT(BlueprintType)
struct FItemTierRollRatio
{
	GENERATED_BODY()
public:
	FItemTierRollRatio()
	{
		m_LegendRatio = 0.0f;
		m_EpicRatio = 0.025f;
		m_RareRatio = 0.05f;
		m_MagicRatio = 0.1f;
	}
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float m_LegendRatio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float m_EpicRatio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float m_RareRatio;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float m_MagicRatio;

	FORCEINLINE_DEBUGGABLE E_ITEMTIER SetRandomTierRoll()  const
	{
		float NormalRatio = 1 - ((*this).m_LegendRatio + (*this).m_EpicRatio + (*this).m_MagicRatio + (*this).m_RareRatio);
		//0.825
		float RandomRatioRolled = FMath::RandRange(0.0f, 1.0f);

		float RatioCalcu = RandomRatioRolled;

		if (RatioCalcu <= NormalRatio)
		{
			return E_ITEMTIER::NORMAL;
		}
		RatioCalcu -= NormalRatio;

		if (RatioCalcu <= (*this).m_MagicRatio)
		{
			return E_ITEMTIER::MAGIC;
		}
		RatioCalcu -= (*this).m_MagicRatio;

		if (RatioCalcu <= (*this).m_RareRatio)
		{
			return E_ITEMTIER::RARE;
		}
		RatioCalcu -= (*this).m_RareRatio;

		if (RatioCalcu <= (*this).m_EpicRatio)
		{
			return E_ITEMTIER::EPIC;
		}
		RatioCalcu -= (*this).m_EpicRatio;

		//if (RatioCalcu <= m_LegendRatio)
		//{
			return E_ITEMTIER::LEGEND;
		//}
	}
};



USTRUCT(BlueprintType)
struct  FDropItemData
{
public:
	GENERATED_BODY()
	FDropItemData()
	{
	}
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle m_DropItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_DropPercentOne = 0.5f;
};

USTRUCT(BlueprintType)
struct FOption
{
	GENERATED_BODY()
public:
	FOption()
	{
		m_OptionType = E_OPTIONTYPE::NONE;
		m_OptionValue.SetValue(1.f);
		m_OptionName = FText::FromString("Socket");
		m_PlusMinus=FText::FromString("");
		m_IsPercV = false;
	}
	E_OPTIONTYPE m_OptionType;
	FStatF m_OptionValue;
	FText m_OptionName;
	FText m_PlusMinus;
private:
	bool m_IsPercV;
private:
	void SetOptionPlus() 
	{
		if (m_OptionValue.GetFinalValue()>=0)
		{
			m_PlusMinus = FText::FromString("+");
			return;
		}
		m_PlusMinus = FText::FromString("-");
	}
public:
	FORCEINLINE void SetOptionType(E_OPTIONTYPE type)
	{
		m_OptionType = type;
	}
	FORCEINLINE void SetOptionName(FText txt)
	{
		m_OptionName= txt;
	}
	FORCEINLINE void SetIsPercValue(bool isPercV)
	{
		m_IsPercV = isPercV;
	}
	FORCEINLINE void SetStatValue(float v)
	{
		m_OptionValue.SetValue(v);
		SetOptionPlus();
	}

	FText ToText(int floatCount=1) const
	{
		if (m_OptionType == E_OPTIONTYPE::NONE)
		{
			return m_OptionName;
		}

		FFormatOrderedArguments Args;
		Args.Add(m_OptionName);
		Args.Add(m_PlusMinus);
		if (m_IsPercV)
		{
			Args.Add(m_OptionValue.ToTextPerc(floatCount));
		}
		else
		{
		Args.Add(m_OptionValue.ToText(floatCount));
		}
		auto FormatT= FTextFormat(FText::FromString("{0}{1}{2}"));
		return FText::Format(FormatT, Args);
	}
};

USTRUCT(BlueprintType)
struct FOptionValue
{
	//use array,index level
	GENERATED_BODY()
public:
	FOptionValue()
	{
		m_MinValue = 0.1f;
		m_MaxValue = 2.f;
	}
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_MinValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_MaxValue;
};