// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightSwitch.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOfActorsOnPlate();

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 70.0f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurPlate = nullptr;
	UPROPERTY(EditAnywhere)
	float TriggerMass = 7.f;
	UPROPERTY(EditAnywhere)
	AActor* Owner = nullptr;
	float CurrentYaw;
	bool VolumeTriggered;
	float WorldTime;
	
};
