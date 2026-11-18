
#include "ArenaManager.h"

#include "MarkerActor.h"
#include "SimAgent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

AArenaManager::AArenaManager()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	RootComponent = SceneRoot;
}

void AArenaManager::BeginPlay()
{
	Super::BeginPlay();

	CreateAgents();
}

void AArenaManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MarkerTimer += DeltaTime;

	if (MarkerTimer >= MarkerInterval)
	{
		MarkerTimer = 0.0f;
		EmitMarkers();
	}
}

void AArenaManager::CreateAgents()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		return;
	}

	const FVector Center = GetActorLocation() + FVector(0.0f, 0.0f, 120.0f);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < AgentCount; ++i)
	{
		const FVector Location = Center + FVector(FMath::FRandRange(-AreaRadius, AreaRadius), FMath::FRandRange(-AreaRadius, AreaRadius), 0.0f);

		ASimAgent* Agent = World->SpawnActor<ASimAgent>(Location, FRotator::ZeroRotator, Params);

		if (Agent)
		{
			Agent->Initialize(Center, AreaRadius, AgentSpeed);
		}
	}
}

void AArenaManager::EmitMarkers()
{
	UWorld* World = GetWorld();

	if (!World || MarkerCount <= 0)
	{
		return;
	}

	const FVector Center = GetActorLocation() + FVector(0.0f, 0.0f, 80.0f);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < MarkerCount; ++i)
	{
		const FVector Location = Center + FVector(FMath::FRandRange(-AreaRadius, AreaRadius), FMath::FRandRange(-AreaRadius, AreaRadius), 0.0f);

		AMarkerActor* Marker = World->SpawnActor<AMarkerActor>(Location, FRotator::ZeroRotator, Params);

		if (Marker)
		{
			Marker->SetLifeSpan(MarkerLife);
		}
	}
}
