// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveToNextPatrolPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "EnemyCharacter.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_MoveToNextPatrolPoint::UBTT_MoveToNextPatrolPoint()
{
	NodeName = TEXT("MoveToNextPatrolPoint");
}

EBTNodeResult::Type UBTT_MoveToNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr) { return EBTNodeResult::Failed; }

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent == nullptr) { return EBTNodeResult::Failed; }

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(AIController->GetPawn());
	if (EnemyCharacter == nullptr) { return EBTNodeResult::Failed; }

	UWorld* World = EnemyCharacter->GetWorld();
	if (World == nullptr) { return EBTNodeResult::Failed; }

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
	if (NavSystem == nullptr) { return EBTNodeResult::Failed; }

	FVector TargetLocation;

	bool PatrolResult = EnemyCharacter->GetNextPatrolLocation(TargetLocation);
	if (!PatrolResult)
	{
		return EBTNodeResult::Failed;
	}

	EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(TargetLocation, 10.0f, false);
	
	if (Result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Result == EPathFollowingRequestResult::Type::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		AIController->GetPathFollowingComponent()->OnRequestFinished.AddLambda(
			[&](FAIRequestID RequestID, const FPathFollowingResult& Result)
			{
				if (Result.Code == EPathFollowingResult::Success)
				{
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				}
				else if (Result.Code == EPathFollowingResult::Aborted)
				{
					FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
				}
				else
				{
					FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				}
			});
	}

	return EBTNodeResult::InProgress;
}
