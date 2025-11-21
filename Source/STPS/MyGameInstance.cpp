#include "MyGameInstance.h"
#include "MoviePlayer.h"

void UMyGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMyGameInstance::BeginLoadingScreen(const FString& InMapName)
{
	FLoadingScreenAttributes LoadingScreen;

	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

	LoadingScreen.MinimumLoadingScreenDisplayTime = 2.0f;

	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void UMyGameInstance::EndLoadingScreen(UWorld* InLoaderWorld)
{

}