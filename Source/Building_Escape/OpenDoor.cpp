// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		ToggleDoor(DeltaTime, TargetYaw); // opens the door
	}
	else {
		ToggleDoor(DeltaTime, InitialYaw); // closes the door
	}
}

void UOpenDoor::ToggleDoor(float DeltaTime, float Target) {
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	//FInterp is better as it ignores the frames
	DoorRotation.Yaw = CurrentYaw = FMath::FInterpTo(CurrentYaw, Target, DeltaTime, 2); // FInterpConstantTo is faster because it is a Linear Interpolation, FInterpTo is smoother
	GetOwner()->SetActorRotation(DoorRotation);
}