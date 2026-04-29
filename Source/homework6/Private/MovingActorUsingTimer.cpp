// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActorUsingTimer.h"

// Sets default values
AMovingActorUsingTimer::AMovingActorUsingTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void AMovingActorUsingTimer::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(fTimerhandle, this, AMovingActorUsingTimer::RepeatingFunction, 3, true, 3);
	//								고유 핸들, 호출될obj, 호출될 obj의 함수, 반생간격(초단위), 반복 여부, 첫 발생 딜레이(0 미만이면 반복시간을 가져감)
	GetWorldTimerManager().SetTimer(fTimerhandle, this, &AMovingActorUsingTimer::RepeatingFunction, 3, true, 3);

}

void AMovingActorUsingTimer::EndPlay(const EEndPlayReason::Type reason)
{
	//타이머는 확실하게 없앨수 있도록 해야함.
	GetWorldTimerManager().ClearTimer(fTimerhandle);
}


void AMovingActorUsingTimer::RepeatingFunction()
{
	FString DebugMsg = FString::Printf(TEXT("RepeatingFunction 호출"));
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Black, DebugMsg);

	//if (true) {
	//	//타이머를 제거하는 방법은 ClearTimer에 fTimerHandle을 호출
	//	GetWorldTimerManager().ClearTimer(fTimerhandle);
	//}
}
