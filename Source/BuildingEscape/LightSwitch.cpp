// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	const FColor Blue;
	PointLightSwitch = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightSwitch"));
	//PointLightSwitch->SetLightColor(FLinearColor(0, 1, 0, 1), true);
	PointLightSwitch->bVisible = true;
	PointLightSwitch->Intensity = 1000.0f;
	PointLightSwitch->LightColor = FColor(255, 0, 0, 1);
	RootComponent = PointLightSwitch;
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();	
}

float ALightSwitch::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TSet<AActor*> OverlappingActors;

	if (!PressurPlate) { return 0; }

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
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PressurPlate) { return; }
	
	//if (PressurPlate->IsOverlappingActor(ActorThatOpens) && (VolumeTriggered == false))
	if ((GetTotalMassOfActorsOnPlate() >= TriggerMass) && (VolumeTriggered == false))
	{
		// if the actor enters the trigger volume
		PointLightSwitch->SetLightColor(FColor(0, 255, 0, 1));
		
		// change the bool value to trigger the effect only once
		VolumeTriggered = true;
	}
	else if ((GetTotalMassOfActorsOnPlate() < TriggerMass) && (VolumeTriggered == true))
	//else if (!PressurPlate->IsOverlappingActor(ActorThatOpens) && (VolumeTriggered == true))
	{
		// if the actor leaves the trigger volume
		PointLightSwitch->SetLightColor(FColor(255, 0, 0, 1));

		// change the bool value to trigger the effect only once
		VolumeTriggered = false;
	}
}
