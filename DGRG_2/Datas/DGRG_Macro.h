// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGRG_Struct.h"
#include "UObject/NoExportTypes.h"
#include "DGRG_Macro.generated.h"


class ADGRG_BaseCharacter;
class AMonsterBase;
struct FStatDefault;
struct FStatChar;
class UStoredItem;
class UStoredEquipItem;
class UStoredMaterialItem;
class UWidgetItemVisual;
/**
 * 
 */
UCLASS()
class DGRG_2_API UDGRG_Macro : public UObject
{
	GENERATED_BODY()
};


DECLARE_LOG_CATEGORY_EXTERN(DGRG_2, Log, All);
#define DGRGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//#define DIA2LOG_S(Verbosity) UE_LOG(Dia2, Verbosity, TEXT("%s"), *DIA2LOG_CALLINFO)
#define DGRGLOG(Format, ...) UE_LOG(DGRG_2, Warning, TEXT("%s %s"), *DGRGLOG_CALLINFO, *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define DGRGCHECK(Expr, ...) {if(!(Expr)) {DGRGLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

#define PRINTF(Format, ...) UE_LOG(DGRG_2, Warning, TEXT("%s"), *FString::Printf(TEXT(Format), ##__VA_ARGS__))
#define PRINTF_STR(str) UE_LOG(DGRG_2, Warning, TEXT("%s"),*str)

#define TEST_BIT(Bitmask, Bit) (((Bitmask) & (static_cast<uint32>(Bit)))>0)
#define SET_BIT(Bitmask, Bit) (Bitmask |= static_cast<uint32>(Bit))
#define CLEAR_BIT(Bitmask, Bit) (Bitmask &= ~( static_cast<uint32>(Bit)))
#define TOFLAG(Enum) ( static_cast<uint32>(Enum))

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByValue((int64)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemDelegate,  UStoredItem*, item, FCoord, gridPivot);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipDelegate, UStoredEquipItem*,item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidVoidBP);
DECLARE_MULTICAST_DELEGATE(FVoidVoid);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidFloatBP, float, _floatParam);
DECLARE_MULTICAST_DELEGATE_OneParam(FVoidFloat, float);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidIntBP, int, _intParam);
//DECLARE_MULTICAST_DELEGATE_OneParam(FVoidInt, int);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidActorBP, AActor*, _interMan);
//DECLARE_MULTICAST_DELEGATE_OneParam(FVoidActor, AActor*);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharDelegate, ADGRG_BaseCharacter*, character);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVoidMonsterBP,AMonsterBase*, monster);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFStatChanged,const FStatDefault&, statDefault);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharStatChanged,const FStatChar&, statChar);


//DECLARE_MULTICAST_DELEGATE_OneParam(FVoidMonster,const AMonsterBase*);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam

