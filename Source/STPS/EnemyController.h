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

public:
	AEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

	UBlackboardComponent* GetBlackboard() { return BlackboardComponent; }
	
protected:
	
	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	TObjectPtr<class UBlackboardComponent> BlackboardComponent;
};
