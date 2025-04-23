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
