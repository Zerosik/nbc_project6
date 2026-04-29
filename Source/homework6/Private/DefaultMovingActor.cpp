// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMovingActor.h"

// Sets default values
ADefaultMovingActor::ADefaultMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 300.f;
	MaxRange = FVector(0.f, 2000.f, 0.f);

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADefaultMovingActor::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("TargetLocation :  %f, %f, %f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
}

void ADefaultMovingActor::OnConstruction(const FTransform& Transform)
{
	//에디터 상의 값이 갱신될 때 마다 호출되는 함수임.
	//디테일 패널 값을 건드려도 갱신이 된다.
	Super::OnConstruction(Transform);
	StartLocation = GetActorLocation(); 
}

// Called every frame
void ADefaultMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TargetLocation = StartLocation + MaxRange;
	distanceTwoPoints = FVector::Dist(StartLocation, TargetLocation);

	if (FVector::Dist(GetActorLocation(), StartLocation) <= 20) {
		direction = 1;
		UE_LOG(LogTemp, Error, TEXT("straight"));
	}

	if (FVector::Dist(GetActorLocation(), TargetLocation) <= 20) {
		direction = -1;
		UE_LOG(LogTemp, Error, TEXT("reverse"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
	}

	FVector moveDirection = (TargetLocation - StartLocation).GetSafeNormal();
	float stepMove = MoveSpeed * DeltaTime;

	FVector stepLocation = GetActorLocation() + moveDirection * stepMove * direction;
	SetActorLocation(stepLocation, true);
}

