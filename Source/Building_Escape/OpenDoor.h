// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ToggleDoor(float DeltaTime, float Target, FString DoorStatus);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void PressurePlateErrorMessage() const;

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;
	bool bOpenDoorSoundPlayed = false;
	bool bCloseDoorSoundPlayed = true;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;
	
	UPROPERTY(EditAnywhere)
		int32 DoorCloseSpeed = 2;

	UPROPERTY(EditAnywhere)
		float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
		float MassNeededToOpen = 50.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;
};
