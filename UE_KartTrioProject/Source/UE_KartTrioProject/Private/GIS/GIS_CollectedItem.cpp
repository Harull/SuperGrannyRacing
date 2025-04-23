// Fill out your copyright notice in the Description page of Project Settings.


#include "GIS/GIS_CollectedItem.h"
#include <Kismet/KismetSystemLibrary.h>


void UGIS_CollectedItem::AddCollectedItem(TObjectPtr<ACollectedItem> _item)
{
	if (!_item) return;
	allCollectedItem.Add(_item);
	//UKismetSystemLibrary::PrintString(this, "Add Collected Item");;
	
}

void UGIS_CollectedItem::RemoveCollectedItem(TObjectPtr<ACollectedItem> _item)
{
	if (!_item) return;
	allCollectedItem.Remove(_item);
}

TArray<TObjectPtr<ACollectedItem>> UGIS_CollectedItem::GetRandomList(int _sizeToList)
{
	int _size = allCollectedItem.Num();
	for (int i = 0; i < _sizeToList; i++)
	{
		int _value = FMath::RandRange(0,_size);
		TObjectPtr<ACollectedItem> _item = allCollectedItem[_value];
		if (allItemToList.Contains(_item)) i--;
		allItemToList.Add(_item);
	}

	return allItemToList;
}

void UGIS_CollectedItem::SetAllItemInList()
{
	int _size = allItemToList.Num();
	for (int i = 0; i < _size; i++)
	{
		allItemToList[i]->SetIsInTheList(true);
	}
}
