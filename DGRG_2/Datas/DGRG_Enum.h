// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "StoredEquipItem.h"
#include "Delegates/Delegate.h"
#include "DGRG_Enum.generated.h"

/**
 * 
 */
UCLASS()
class DGRG_2_API UDGRG_Enum : public UObject
{
	GENERATED_BODY()
	
};



UENUM(BlueprintType)
enum class E_INVEN : uint8
{
	GRIDSIZE = 50
};

//UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
UENUM(BlueprintType)
enum class  E_EQUIPMENT : uint8
{
	EMPTY,
	ONEHAND,
	SHIELD,
	TWOHAND,
	DAGGER,
	KATANA,
	HEAD,
	NECK,
	TORSO,
	BELT,
	SHOE,
	GLOVE,
	RING,
	LEGNTH
};

//ENUM_CLASS_FLAGS(E_EQUIPMENT);
//




UENUM(BlueprintType)
enum class E_STANCE : uint8
{//애니매이션 구분

	EMPTY,
	ONEHAND,
	SHIELD,
	DUALWIELD,
	TWOHAND,
	DAGGER,
	KATANA,
	LENGTH
};
UENUM(BlueprintType)
enum class E_ATTACKTYPE : uint8
{
	PHYSICAL,
	FIRE,
	ELECTRIC,
	SOUL
};

UENUM(BlueprintType)
enum class E_UNITID : uint8
{//아군적군 구분
	//생중립
	//몬스터
	//사람
	NEUTRAL,
	MONSTER,
	HUMAN,
	LENGTH
};

UENUM(BlueprintType)
enum class E_ITEMTIER : uint8
{
	NORMAL,
	MAGIC,
	RARE,
	EPIC,
	LEGEND,
	LENGTH
};

UENUM(BlueprintType)
enum class E_DIFFICULTY : uint8
{
	VERYEASY,
	EASY,
	NORMAL,
	MYTHIC,
	LEGEND,
	PILGRIMAGE1,
	PILGRIMAGE2,
	PILGRIMAGE3,
	LENGTH
};

UENUM(BlueprintType)
enum class E_ITEMTYPE : uint8
{
	NORMAL,
	EQUIP,
	MATERIAL,
	ENCHANT,
	GEM,
	LENGTH
};


enum class E_GLOBAL_CONST
{

	STATOFFSET = 50,

	MAXGOLD = 9999999,

	MAXLEVEL = 50,

	SLOTSIZE = 50,

	THOUS = 1000,

	MILE = 10000,

	MAXSTAT = 1410065400,//1410065407

	MAXSTAGE = 1000

};

UENUM(BlueprintType)
enum class E_OPTIONTYPE : uint8
{
	NONE,
	HP_Per,
	HP_Abs,
	AS_Per,
	AS_Abs,
	MS_Per,
	MS_Abs,
	DMG_Per,
	DMG_Abs,
	AM_Per,
	AM_Abs,
	FM_Per,
	FM_Abs,
	EM_Per,
	EM_Abs,
	SM_Per,
	SM_Abs,
	EXS_Per,
	DRR_Per,
	GLDS_Per,


	STR_Abs,
	AGIL_Abs,
	LUCK_Abs,
	LENGTH
};