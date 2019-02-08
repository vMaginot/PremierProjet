// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void FindPhysicsHandleComponent(); // Find attached physics component
	void SetupInputComponent(); // Find and setup attached input component
	
private:
	float Reach = 100.f; // length of debug line		
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* PlayerInput = nullptr;
	void Grab(); // Ray cast and grab what is in reach
	void Release(); // Release what has been grabbed by the player

	
	FHitResult GetFirstPhysicsInReach() const; // return hit for 1st physics body in reach
	FVector GetReachLineStart() const;
	FVector GetReachLineEnd() const;
};
