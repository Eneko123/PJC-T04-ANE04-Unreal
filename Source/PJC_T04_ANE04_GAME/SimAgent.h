
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimAgent.generated.h"

class UStaticMeshComponent;

UCLASS()
class PJC_T04_ANE04_GAME_API ASimAgent : public AActor
{
    GENERATED_BODY()

public:
    ASimAgent();

    virtual void Tick(float DeltaTime) override;

    void Initialize(const FVector& InCenter, float InRadius, float InSpeed);

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Mesh;

    FVector Center = FVector::ZeroVector;
    FVector Destination = FVector::ZeroVector;

    float Radius = 650.0f;
    float Speed = 180.0f;

    void PickDestination();
    ASimAgent* FindNearbyAgent() const;
    FVector ScanAhead(const FVector& Direction) const;
};
