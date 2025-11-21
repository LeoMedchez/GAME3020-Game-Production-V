#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class STPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoaderWorld);

};
