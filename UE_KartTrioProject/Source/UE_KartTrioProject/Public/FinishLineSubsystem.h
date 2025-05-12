// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FinishLineSubsystem.generated.h"


class AFinishLine;
UCLASS()
class UE_KARTTRIOPROJECT_API UFinishLineSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	TArray<TObjectPtr<AFinishLine>> allFinishLine;

public:
	FORCEINLINE const TArray<TObjectPtr<AFinishLine>>& GetAllFinishLines() const { return allFinishLine; }
	TObjectPtr<AFinishLine> GetClosestAvailableFinish(const FVector& FromLocation) const;
	void RegisterFinishLine(AFinishLine* FinishLine);



};
