// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

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

	// Find the owning actor
	Owner = GetOwner();

	if (!PressurPlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
	}
}


void UOpenDoor::OpenDoor()
{	
	// Get current yaw for the door
	CurrentYaw = Owner->GetActorRotation().Yaw;
	// Rotate the door	
	Owner->SetActorRotation(FRotator(0.f, CurrentYaw - OpenAngle, 0.0f));
}


void UOpenDoor::CloseDoor()
{
	// Get current yaw for the door
	CurrentYaw = Owner->GetActorRotation().Yaw;
	// Rotate the door	
	Owner->SetActorRotation(FRotator(0.f, CurrentYaw + OpenAngle, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TSet<AActor*> OverlappingActors;

	if (!PressurPlate) { return TotalMass; }

	// find all overlaping actors
	PressurPlate->GetOverlappingActors(OUT OverlappingActors);

	// iterate through them and add their mass
	for (const auto& Actor:OverlappingActors)
	{		
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("Actor name : %s"), *Actor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Actor Mass : %f"), Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass());
	}

	return TotalMass;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//WorldTime = GetWorld()->GetTimeSeconds();

	// Poll the trigger volume
	if ((GetTotalMassOfActorsOnPlate() >= TriggerMass) && (VolumeTriggered == false))
	{
		// if the actor enters the trigger volume
		OpenDoor();
		//MyLight->changeColor(FColor(0, 255, 0, 1));

		// change the bool value to trigger the effect only once
		VolumeTriggered = true;
	}
	else if ((GetTotalMassOfActorsOnPlate() < TriggerMass) && (VolumeTriggered == true))
	{
		// if the actor leaves the trigger volume
		CloseDoor();
		// change the bool value to trigger the effect only once
		VolumeTriggered = false;
	}
}
