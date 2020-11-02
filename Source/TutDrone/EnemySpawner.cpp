// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Engine/World.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnArea->SetBoxExtent(FVector(10000.0f, 10000.0f, 100.0f));
}

void AEnemySpawner::SpawnEnemy()
{
	FVector Origin;
	FVector Extents;
	GetActorBounds(false, Origin, Extents);
	FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extents);

	GetWorld()->SpawnActor<AEnemy>(EnemyType, SpawnPoint, FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::SpawnEnemy, SpawnSpan, true);

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

