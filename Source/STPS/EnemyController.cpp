// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"
#include <Kismet/GameplayStatics.h>
#include "MainCharacter.h"

AEnemyController::AEnemyController()
	:Super()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);

	PerceptionComponent = CreateDefaultSubobject <UAIPerceptionComponent>(TEXT("PerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(FName("Hearing Config"));

	SightConfig->SightRadius = 700.0f;
	SightConfig->LoseSightRadius = 900.0f;
	SightConfig->PeripheralVisionAngleDegrees = 45;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	HearingConfig->HearingRange = 900.0f;
	HearingConfig->SetMaxAge(2);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->ConfigureSense(*HearingConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetPerceptionUpdated);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn);
	if (Enemy)
	{
		if (Enemy->BehaviorTree)
		{
			if (Enemy->BehaviorTree->BlackboardAsset)
			{
				BlackboardComponent->InitializeBlackboard(*(Enemy->BehaviorTree->BlackboardAsset));
			}
			BehaviorTreeComponent->StartTree(*(Enemy->BehaviorTree));
		}
	}
}

void AEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor == nullptr) return;

	if (AMainCharacter* PlayerRef = Cast<AMainCharacter>(Actor))
	{
		if (Stimulus.Type == SightConfig->GetSenseID())
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				bCanSeePlayer = true;
				BlackboardComponent->SetValueAsBool("IsInvestigating", bCanSeePlayer);
			}
			else
			{
				bCanSeePlayer = false;
				BlackboardComponent->SetValueAsBool("IsInvestigating", bCanSeePlayer);
			}
		}

		if (Stimulus.Type == HearingConfig->GetSenseID())
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				bHeardSound = true;
			}
			else
			{
				bHeardSound = false;
			}
		}
	}
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCanSeePlayer)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("Player Seen"));
	}

	if (bHeardSound)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("Player Heard"));
	}
}