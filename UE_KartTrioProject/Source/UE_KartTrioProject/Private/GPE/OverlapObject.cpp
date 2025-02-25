// Fill out your copyright notice in the Description page of Project Settings.


#include "GPE/OverlapObject.h"

// Sets default values
AOverlapObject::AOverlapObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionProfileName("OverlapAll");
}

// Called when the game starts or when spawned
void AOverlapObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverlapObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverlapObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	EnterAction();
}

