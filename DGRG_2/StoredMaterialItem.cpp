// Fill out your copyright notice in the Description page of Project Settings.


#include "StoredMaterialItem.h"
#include "DataTableRowBase.h"

UStoredMaterialItem::UStoredMaterialItem()
{
	m_MatItemData = nullptr;
}


const FMaterialItemData * UStoredMaterialItem::GetMatItemData() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_MatItemData;
}

void UStoredMaterialItem::SetItemData(const FBaseItemData * baseData)
{
	Super::SetItemData(baseData);
	m_MatItemData = (FMaterialItemData*)(&baseData);

}
