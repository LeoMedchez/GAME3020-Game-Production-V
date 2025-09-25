// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (auto PatrolPoint : LocalPatrolPoints)
	{
		WorldPatrolPoints.Add(PatrolPoint + GetActorLocation());
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEnemyCharacter::GetNextPatrolLocation(FVector& Location)
{
	if (WorldPatrolPoints.Num() == 0)
	{
		return false;
	}

	if (CurrentPatrolIndex >= WorldPatrolPoints.Num())
	{
		CurrentPatrolIndex = 0;
	}

	Location = WorldPatrolPoints[CurrentPatrolIndex++];
	return true;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

