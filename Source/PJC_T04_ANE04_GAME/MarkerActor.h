
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarkerActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class PJC_T04_ANE04_GAME_API AMarkerActor : public AActor
{
    GENERATED_BODY()

public:
    AMarkerActor();

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Mesh;
};
