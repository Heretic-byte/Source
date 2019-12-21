// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemContainer.h"

UItemContainer::UItemContainer() :
	m_InvenWidthHeight(10, 8),
	m_Container()

{
	SetComponentTickEnabled(false);
}

void UItemContainer::SetContainer()
{
	m_Container.Init(TArray<UStoredItem*>(),m_InvenWidthHeight.nX);

	for (int i = 0; i < m_Container.Num(); i++)
	{
		m_Container[i].Init(nullptr,m_InvenWidthHeight.nY);
	}

}

bool UItemContainer::SearchAbleSpaceAll(  UStoredItem*  item, FCoord * result)
{
	return SearchAbleSpace(FCoord(0, 0), FCoord(m_InvenWidthHeight.nX, m_InvenWidthHeight.nY), item, result);
}

bool UItemContainer::SearchAbleSpace(FCoord leftTop, FCoord rightBtm,   UStoredItem* item, FCoord * result)
{
	int ItemWidth = item->GetItemSize().nX;
	int ItemHeight = item->GetItemSize().nY;

	for (int x = leftTop.nX; x < rightBtm.nX; x++)
	{
		int HeightCount = 0;
		for (int y = leftTop.nY; y < rightBtm.nY; y++)
		{
			if (m_Container[x][y])
			{
				HeightCount = 0;
				continue;
			}

			HeightCount++;

			if (HeightCount >= ItemHeight)
			{
				FCoord pivot = FCoord(x, y - ItemHeight + 1);

				FCoord pivotRightBtm = FCoord(pivot.nX + item->GetItemSize().nX - 1, pivot.nY + item->GetItemSize().nY - 1);

				if (pivotRightBtm.nX >= m_InvenWidthHeight.nX || pivotRightBtm.nY >= m_InvenWidthHeight.nY)
				{
					return false;
				}

				if (CheckCanbeAddItemAreaFast(pivot, pivotRightBtm))
				{
					*result = pivot;
					return true;
				}
				//그상황임

			}
		}
	}

	return false;
}

bool UItemContainer::CheckCanbeAddItemAreaFast(FCoord leftTop, FCoord rightBtm)
{
	int i = 0;

	int xEnd = rightBtm.nX;
	int yEnd = rightBtm.nY;


	for (int x = leftTop.nX; x <= xEnd; x++)
	{
		for (int y = leftTop.nY; y <= yEnd; y++)
		{
			i += 1;
			if (m_Container[x][y])
			{
				return false;
			}
		}
	}

	return true;
}

void UItemContainer::SetInstacneToSlot(FCoord resultCoodPivot,   UStoredItem *   dItem)
{
	int pX = resultCoodPivot.nX;
	int pY = resultCoodPivot.nY;
	int wX = pX + dItem->GetItemSize().nX;
	int wY = pY + dItem->GetItemSize().nY;

	for (int x = pX; x < wX; x++)
	{
		for (int y = pY; y < wY; y++)
		{
			m_Container[x][y] = dItem;
		}
	}
}

bool UItemContainer::SetNullInstacneToSlot(FCoord leftTop,   UStoredItem* dItem)
{
	int pX = leftTop.nX;
	int pY = leftTop.nY;

	int wX = pX + dItem->GetItemSize().nX;
	int wY = pY + dItem->GetItemSize().nY;

	for (int x = pX; x < wX; x++)
	{
		for (int y = pY; y < wY; y++)
		{

			m_Container[x][y] = nullptr;
		}
	}

	return true;
}

bool UItemContainer::AddItemToEmptySpace(UStoredItem* dItem, FCoord& resultPivot)
{

	FCoord Result;

	if (!SearchAbleSpaceAll(dItem, &Result))
	{
		resultPivot = Result;
		PRINTF("Fail Add Item");
		return false;
	}

	resultPivot = Result;

	SetInstacneToSlot(Result, dItem);
	if (OnItemAdd.IsBound())
		OnItemAdd.Broadcast(dItem, Result);

	return true;
}

bool UItemContainer::AddItemToPivot(FCoord pivot, UStoredItem* dItem)
{
	if (!CheckCanbeAddItemArea(pivot, dItem))
	{
		return false;
	}

	SetInstacneToSlot(pivot, dItem);

	if (OnItemAdd.IsBound())
		OnItemAdd.Broadcast(dItem, pivot);

	return true;
}

bool UItemContainer::RemoveItemFromPivot(FCoord pivot, UStoredItem* dItem)
{
	return SetNullInstacneToSlot(pivot, dItem);
}

bool UItemContainer::RemoveItemFromAuto(UStoredItem* dItem)
{
	//아직
	return false;
}

bool UItemContainer::CheckCanbeAddItemArea(FCoord leftTop, UStoredItem* dItem)
{
	if (leftTop.nX < 0 || leftTop.nY < 0)
	{
		return false;
	}

	if (leftTop.nX >= m_InvenWidthHeight.nX || leftTop.nY >= m_InvenWidthHeight.nY)
	{
		return false;
	}

	FCoord rightBtm = FCoord(leftTop.nX + dItem->GetItemSize().nX - 1, leftTop.nY + dItem->GetItemSize().nY - 1);

	if (rightBtm.nX < 0 || rightBtm.nY < 0)
	{
		return false;
	}
	if (rightBtm.nX >= m_InvenWidthHeight.nX || rightBtm.nY >= m_InvenWidthHeight.nY)
	{
		return false;
	}

	return CheckCanbeAddItemAreaFast(leftTop, rightBtm);
}


void UItemContainer::PrintDebug()
{
	for (int y = 0; y < m_InvenWidthHeight.nY; y++)
	{
		FString debugRaw = FString();
		for (int x = 0; x < m_InvenWidthHeight.nX; x++)
		{

			if (m_Container[x][y])
			{
				debugRaw += 'O';
			}
			else
			{
				debugRaw += 'X';
			}

		}

		PRINTF_STR(debugRaw);
	}
}

void UItemContainer::SetContainerSize(int width, int height)
{
	m_InvenWidthHeight.nX = width;
	m_InvenWidthHeight.nY = height;
}
