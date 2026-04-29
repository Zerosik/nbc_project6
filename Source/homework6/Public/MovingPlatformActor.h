// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatformActor.generated.h"

UCLASS()
class HOMEWORK6_API AMovingPlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatformActor();
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement|Checkpoints", meta=(Tooltip="이동할 지점, 최소 2개 필요."))
	TArray<FVector> Checkpoints;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (Tooltip = "True이면 이동 완료후 종료지점에서 시작지점으로 이동\nfalse이면 처음지점으로 순간이동하여 다시 이동."))
	bool RoundTrip;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (Tooltip = "이동속도."))
	float MoveSpeed;
private:
	//Checkpoints[currentIndex]로 이동함
	int currentIndex = 1;
	//방향, 1이면 정방향, -1이면 역방향,
	int direction = 1;

	bool HasValidCheckpoint();
	void ChangeTargetIndex();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
