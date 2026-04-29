// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PendulumActor.generated.h"

UCLASS()
class HOMEWORK6_API APendulumActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APendulumActor();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;


	UPROPERTY(EditInstanceOnly, Category = "Pendulum")
	float MaxAngle;
	UPROPERTY(EditInstanceOnly, Category = "Pendulum")
	float SwingSpeed;

	float defaultYaw;
	float timeElapsed;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
