// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "LightSwitch.generated.h"
UCLASS()
class BUILDINGESCAPE_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class UPointLightComponent* PointLightSwitch = nullptr;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurPlate = nullptr;
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;
	UPROPERTY(EditAnywhere)
	float TriggerMass = 7.f;
	bool VolumeTriggered;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float GetTotalMassOfActorsOnPlate();

};
