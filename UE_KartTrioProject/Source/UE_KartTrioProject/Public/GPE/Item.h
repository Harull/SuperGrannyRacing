#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeniorPlayer.h"
#include "Item.generated.h"



UCLASS(Abstract)
class UE_KARTTRIOPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)TObjectPtr<UTexture2D> itemImage = nullptr;

public:
	FORCEINLINE TObjectPtr<UTexture2D> GetItemImage() { return itemImage; }
	
public:	
	AItem();

public:
	virtual void Use(ASeniorPlayer* _player) PURE_VIRTUAL(AItem::Use, );


};
