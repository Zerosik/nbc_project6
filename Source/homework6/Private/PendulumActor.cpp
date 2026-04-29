// Fill out your copyright notice in the Description page of Project Settings.


#include "PendulumActor.h"

// Sets default values
APendulumActor::APendulumActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootComponent);

	MaxAngle = 45.f;
	SwingSpeed = 5.f;
	timeElapsed = 0.f;
}

// Called when the game starts or when spawned
void APendulumActor::BeginPlay()
{
	Super::BeginPlay();
	defaultYaw = GetActorRotation().Yaw;
}

// Called every frame
void APendulumActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeElapsed += DeltaTime;
	//사인파를 이용해 반복하는 애니메이션 구현 가능
	//https://zerosik00.tistory.com/39
	float sine = FMath::Sin(timeElapsed * SwingSpeed);

	//Pitch값으로 진자운동
	FRotator newRotate = FRotator(MaxAngle * sine, defaultYaw, 0.f);
	SetActorRelativeRotation(newRotate);
}

