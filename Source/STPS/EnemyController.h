// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class STPS_API AEnemyController : public AAIController
{
	GENERATED_BODY()

	FTimerHandle RandomWaypointTimerHandle;

protected:
	virtual void BeginPlay() override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

public:
	UFUNCTION()
	void GoToNextPatrolPoint();
	
};
