// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultMovingActor.generated.h"

UCLASS()
class HOMEWORK6_API ADefaultMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefaultMovingActor();
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleInstanceOnly, Category="Movement")
	FVector StartLocation;
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	FVector MaxRange;
private:
	int direction = 1;
	FVector TargetLocation;
	float distanceTwoPoints;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
};
