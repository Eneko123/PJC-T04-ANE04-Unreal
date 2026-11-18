
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArenaManager.generated.h"

class USceneComponent;

UCLASS()
class PJC_T04_ANE04_GAME_API AArenaManager : public AActor
{
	GENERATED_BODY()

public:
	AArenaManager();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, Category = "Simulation", meta = (ClampMin = "1", ClampMax = "1500"))
	int32 AgentCount = 120;

	UPROPERTY(EditAnywhere, Category = "Simulation")
	float AreaRadius = 650.0f;

	UPROPERTY(EditAnywhere, Category = "Simulation")
	float AgentSpeed = 180.0f;

	UPROPERTY(EditAnywhere, Category = "Markers", meta = (ClampMin = "0", ClampMax = "150"))
	int32 MarkerCount = 45;

	UPROPERTY(EditAnywhere, Category = "Markers", meta = (ClampMin = "0.1"))
	float MarkerInterval = 2.5f;

	UPROPERTY(EditAnywhere, Category = "Markers", meta = (ClampMin = "0.1"))
	float MarkerLife = 0.9f;

	float MarkerTimer = 0.0f;

	void CreateAgents();
	void EmitMarkers();
};
