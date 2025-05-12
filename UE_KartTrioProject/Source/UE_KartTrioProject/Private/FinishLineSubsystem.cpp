// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLineSubsystem.h"
#include "GPE/FinishLine.h"
#include <Kismet/KismetSystemLibrary.h>


TObjectPtr<AFinishLine> UFinishLineSubsystem::GetClosestAvailableFinish(const FVector& _fromLocation) const
{
	AFinishLine* _closest = nullptr;
	float _minDistance = TNumericLimits<float>::Max(); // max float
	UKismetSystemLibrary::PrintString(GetWorld(), FString::FromInt(allFinishLine.Num()), true, true, FLinearColor::MakeRandomColor());
	for (AFinishLine* _line : allFinishLine)
	{
		if (_line && _line->GetIsAvailable()) 
		{
			float _dist = FVector::Dist(_line->GetActorLocation(), _fromLocation);
			if (_dist < _minDistance)
			{
				_minDistance = _dist;
				_closest = _line;
			}
		}
	}
	return _closest;
}


void UFinishLineSubsystem::RegisterFinishLine(AFinishLine* _finishLine)
{
	if (_finishLine && !allFinishLine.Contains(_finishLine))
	{
		allFinishLine.Add(_finishLine);
	}
}