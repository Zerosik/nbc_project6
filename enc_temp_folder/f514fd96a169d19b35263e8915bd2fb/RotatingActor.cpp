// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

// Sets default values
ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RotatePerSecond = 1;


	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	//루트는 SetRootComponent로 붙여야함!
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("Cylinder"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	//static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse"));
	//if (MaterialAsset.Succeeded())
	//{
	//	StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	//}
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rotator(0, RotateAngle * RotatePerSecond * DeltaTime, 0);
	AddActorLocalRotation(rotator);
}

