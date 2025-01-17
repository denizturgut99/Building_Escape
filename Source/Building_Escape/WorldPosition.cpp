// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	/*FString Log = TEXT("TEST");
	FString* PtrLog = &Log;

	Log.Len();

	PtrLog->Len();

	UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);*/

	FString ObjectName = GetOwner()->GetName();
	FString ObjectLocation = GetOwner()->GetTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *ObjectName, *ObjectLocation);
	UE_LOG(LogTemp, Error, TEXT("%s is located at %s"), *ObjectName, *ObjectLocation);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

