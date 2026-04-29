// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnArea.generated.h"

class UBoxComponent;

UCLASS()
class HOMEWORK6_API ASpawnArea : public AActor
{
	GENERATED_BODY()
private:
	FTimerHandle spawnHandler;
	FTimerHandle destroyHandler;
	TQueue<AActor*> spawnActorQueue;

public:
	ASpawnArea();

	UBoxComponent* RootComponent;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AActor> SpawnObjectClass;


	void SpawnActor();
	void RemoveActor();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
