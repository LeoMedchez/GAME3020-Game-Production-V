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

const FVector& AEnemyCharacter::GetNextPatrolLocation()
{
	if (WorldPatrolPoints.Num() > 0)
	{
		if (CurrentPatrolIndex >= WorldPatrolPoints.Num())
		{
			CurrentPatrolIndex = 0;
		}

		return WorldPatrolPoints[CurrentPatrolIndex++];
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, 
			TEXT("No Patrol Points Set For Enemy Actor"));
		return FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

