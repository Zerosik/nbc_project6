// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformActor.h"

// Sets default values
AMovingPlatformActor::AMovingPlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Checkpoints.Add(GetActorLocation());
	Checkpoints.Add(GetActorLocation()+FVector(100,0,0));
	RoundTrip = false;
	MoveSpeed = 300.f;


	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AMovingPlatformActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(Checkpoints[0]);
}

// Called every frame
void AMovingPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	FVector targetLocation = Checkpoints[currentIndex];

	//A에서 B로가는 방향벡터 : B벡터 - A벡터 후 GetSafeNormal로 방향벡터를 얻을 수 있음.
	FVector TargetDirection = (targetLocation - currentLocation).GetSafeNormal();
	//두 벡터의 거리는 Dist로 쉽게 구할 수 있음.
	float distance = FVector::Dist(currentLocation, targetLocation);

	if (distance < 10.f) {
		//거의 도착했다면 목표지점을 변경함.
		SetActorLocation(targetLocation);
		ChangeTargetIndex();
	}
	else {	
		//목표지점보다 더 가지 않도록 조정함.
		float step = MoveSpeed * DeltaTime;
		if (step > distance) {
			step = distance;
		}
		//방향X이번 프레임 이동거리
		FVector newLocation = currentLocation + (step * TargetDirection);
		SetActorLocation(newLocation);


	}

}

bool AMovingPlatformActor::HasValidCheckpoint()
{
	//checkpoints 는 최소 2개 지점이 있어야 함.
	return Checkpoints.Num()>=2;
}

void AMovingPlatformActor::ChangeTargetIndex()
{
	//A지점에서 B지점으로 이동이 완료되면 호출하고, 조건에 따라 다음 지점을 정함.

	if (currentIndex == Checkpoints.Num()-1 or currentIndex == 0) {
		//최종지점에 도착하였다면?
		if (RoundTrip) {
			//RoundTrip이면 방향을 반대로 변경.
			direction *= -1;
			currentIndex += direction;
		}
		else {
			//왕복을 하지 않는다면, 0번지점으로 순간이동후 1번지점으로 가도록
			SetActorLocation(Checkpoints[0]);
			currentIndex = 1;
			direction = 1;
		}
	}
	else {
		currentIndex += direction;
	}
}

