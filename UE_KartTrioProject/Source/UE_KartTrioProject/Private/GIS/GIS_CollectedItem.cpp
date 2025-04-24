// Fill out your copyright notice in the Description page of Project Settings.


#include "GIS/GIS_CollectedItem.h"
#include <Kismet/KismetSystemLibrary.h>


void UGIS_CollectedItem::AddCollectedItem(TObjectPtr<ACollectedItem> _item)
{
	if (!_item) return;
	allCollectedItem.Add(_item);
}

void UGIS_CollectedItem::RemoveCollectedItem(TObjectPtr<ACollectedItem> _item)
{
	if (!_item) return;
	allCollectedItem.Remove(_item);
}

TArray<TObjectPtr<ACollectedItem>> UGIS_CollectedItem::GetRandomList(int _sizeToList)
{
	if (allCollectedItem.Num() < _sizeToList) return TArray<TObjectPtr<ACollectedItem>>();
	if (!ItemListIsEmpty()) return allItemToList;

	TArray<TObjectPtr<ACollectedItem>> _allItemToList = allCollectedItem;
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(allCollectedItem.Num()));

	for(ACollectedItem* _item : allCollectedItem)
	{
		if (!_item->GetIsInList())
			_allItemToList.Remove(_item);
	}
	allItemToList = _allItemToList;

	/*for (int i = 0; i < _sizeToList; i++)
	{
		int _size = _allItemToList.Num();
		int _value = FMath::RandRange(0,_size - 1);
		TObjectPtr<ACollectedItem> _item = _allItemToList[_value];
		_allItemToList.RemoveAt(_value);
		if (!_item->GetIsInList()) continue;

		//if (allItemToList.Contains(_item))
		//{
		//	i--;
		//	continue;
		//}

		allItemToList.Add(_item);
	}*/
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(allItemToList.Num()));

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
