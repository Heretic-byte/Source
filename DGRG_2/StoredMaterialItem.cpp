// Fill out your copyright notice in the Description page of Project Settings.


#include "StoredMaterialItem.h"
#include "DataTableRowBase.h"

UStoredMaterialItem::UStoredMaterialItem()
{
	m_MatItemData = nullptr;
}


const FMaterialItemData * UStoredMaterialItem::GetMatItemData() const
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_MatItemData;
}

void UStoredMaterialItem::SetItemData(const FBaseItemData * baseData)
{
	Super::SetItemData(baseData);
	m_MatItemData = (FMaterialItemData*)(&baseData);

}
