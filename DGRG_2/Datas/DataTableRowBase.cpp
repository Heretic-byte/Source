// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableRowBase.h"
//#include "StoredItem.h"
//#include "StoredMaterialItem.h"
//#include "StoredEquipItem.h"

//UStoredItem* FBaseItemData::CreateItem() const
//{
//	auto Item = NewObject<UStoredItem>();
//
//	Item->SetItemData(*this);
//
//	return Item;
//}

const  FTextFormat FScaleStatPercTable::FormatToText =
FTextFormat(FText::FromString("Health:{0}% \n Dmg:{1}% \n Exp:{2}% \n Drop:{3}% \n Gold:{4}% \n"));
