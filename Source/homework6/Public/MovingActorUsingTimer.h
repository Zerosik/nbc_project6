// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActorUsingTimer.generated.h"

UCLASS()
class HOMEWORK6_API AMovingActorUsingTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActorUsingTimer();
private:
	FTimerHandle fTimerhandle;
	void RepeatingFunction();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type reason) override;

};
