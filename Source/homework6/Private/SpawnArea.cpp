// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "DefaultMovingActor.h"
#include "Components/BoxComponent.h"
#include "SpawnArea.h"

// Sets default values
ASpawnArea::ASpawnArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComp"));
	SetRootComponent(RootComponent);


	//혹시 모르니 AActor로 설정하여 다른 액터 사용가능하도록 하고, MovingDefaultActor라면 스폰할때 따로 설정
	static ConstructorHelpers::FClassFinder<AActor> BPAsset(TEXT("/Game/Blueprint/BP_DefaultMovingActor"));
	if (BPAsset.Succeeded())
	{
		SpawnObjectClass = BPAsset.Class;
	}
}

void ASpawnArea::SpawnActor()
{
	//FString DebugMsg = FString::Printf(TEXT("ASpawnArea::SpawnActor called"));
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Yellow, TEXT("ASpawnArea::SpawnActor called Time: ") + FDateTime::Now().ToString());


	//UKismetMathLibrary::RandomPointInBoundingBox으로 박스 범위 내 랜덤 지점을 반환
	//박스의 중심점과 반폭(half-size)를 파라미터로 사용, GetScaledBoxExtent()로 스케일이 적용된 halfsize를 얻을 수 있음.
	FVector rVector = UKismetMathLibrary::RandomPointInBoundingBox(RootComponent->GetComponentLocation(), RootComponent->GetScaledBoxExtent());

	GEngine->AddOnScreenDebugMessage(2, 3, FColor::Yellow, FString::Printf(TEXT("rVector: %f, %f, %f "), rVector.X, rVector.Y, rVector.Z));

	AActor* spawnedActorBase = GetWorld()->SpawnActor<AActor>(SpawnObjectClass, FTransform(FRotator(0), rVector, FVector(1)));

	//
	ADefaultMovingActor* moveActor = Cast<ADefaultMovingActor>(spawnedActorBase);
	if (moveActor) {
		moveActor->MoveSpeed = 1000;
		moveActor->MaxRange = FVector(0, 9999, 0);
		GEngine->AddOnScreenDebugMessage(3, 3, FColor::Yellow, FString::Printf(TEXT("Set Speed and Range")));
	}
	spawnActorQueue.Enqueue(spawnedActorBase);
}

void ASpawnArea::RemoveActor()
{
	AActor* deque;
	if (spawnActorQueue.Dequeue(deque)) {
		deque->Destroy();
		GEngine->AddOnScreenDebugMessage(4, 3, FColor::Yellow, FString::Printf(TEXT("Call Destroy")));
	}
}

// Called when the game starts or when spawned
void ASpawnArea::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(spawnHandler, this, &ASpawnArea::SpawnActor, 3, true, 3);
	GetWorldTimerManager().SetTimer(destroyHandler, this, &ASpawnArea::RemoveActor, 3, true, 9);
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, TEXT("Timer Set"));

}

// Called every frame
void ASpawnArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

