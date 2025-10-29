// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>
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

public:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bCanSeePlayer;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHeardSound;

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	TObjectPtr<class UAISenseConfig_Hearing> HearingConfig;
};
