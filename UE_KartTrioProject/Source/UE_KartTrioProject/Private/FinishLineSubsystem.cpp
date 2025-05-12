// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLineSubsystem.h"
#include "GPE/FinishLine.h"
#include <Kismet/KismetSystemLibrary.h>


const int UFinishLineSubsystem::GetUnavailableFinishLineCount()
{
	int _result = 1;
	UKismetSystemLibrary::PrintString(GetWorld(), "Finish line count : " + FString::FromInt(_result), true, true, FLinearColor::Black, 20.0);

	for (int _i = 0; _i < allFinishLine.Num(); _i++)
	{
		bool _test = allFinishLine[_i]->GetIsAvailable();
		FString _str = _test ? "true" : "false";
		UKismetSystemLibrary::PrintString(GetWorld(), "Bool is available : " + _str, true, true, FLinearColor::Black, 20.0);
		if (!_test)
			_result += 1;
	}
	 UKismetSystemLibrary::PrintString(GetWorld(), "result number : " + FString::FromInt(_result), true, true, FLinearColor::Black, 20.0);
	return _result;
}

TObjectPtr<AFinishLine> UFinishLineSubsystem::GetClosestAvailableFinishLine(const FVector& _fromLocation) const
{
	AFinishLine* _closest = nullptr;
	float _minDistance = 999999999;
	// UKismetSystemLibrary::PrintString(GetWorld(), FString::FromInt(allFinishLine.Num()), true, true, FLinearColor::Black, 20.0);
	for (AFinishLine* _line : allFinishLine)
	{
		if (_line && _line->GetIsAvailable())
		{
			//UKismetSystemLibrary::PrintString(GetWorld(), "Step 1", true, true, FLinearColor::Black, 20.0);

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