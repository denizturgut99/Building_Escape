// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = 90.f;
	
	GetOwner()->SetActorRotation(CurrentRotation);*/
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it but no pressure plate was assigned."), *GetOwner()->GetName());
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() >= MassNeededToOpen) {
		ToggleDoor(DeltaTime, TargetYaw);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else {
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay) {
			ToggleDoor(DeltaTime, InitialYaw);
		}
	}
}

void UOpenDoor::ToggleDoor(float DeltaTime, float Target) {
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	//FInterp is better as it ignores the frames
	DoorRotation.Yaw = CurrentYaw = FMath::FInterpTo(CurrentYaw, Target, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s returned NULL! Check the pressure plate pointer."), *GetOwner()->GetName());
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (int32 i = 0; i < OverlappingActors.Num(); i++) {
		TotalMass += OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}