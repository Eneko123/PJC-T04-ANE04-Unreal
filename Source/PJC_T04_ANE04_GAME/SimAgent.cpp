
#include "SimAgent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ASimAgent::ASimAgent()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCastShadow(false);
	Mesh->SetRelativeScale3D(FVector(0.35f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
	}
}

void ASimAgent::Initialize(const FVector& InCenter, float InRadius, float InSpeed)
{
	Center = InCenter;
	Radius = InRadius;
	Speed = InSpeed;

	PickDestination();
}

void ASimAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Current = GetActorLocation();

	if (FVector::DistSquared(Current, Destination) < 2500.0)
	{
		PickDestination();
	}

	FVector Direction = (Destination - Current).GetSafeNormal();

	ASimAgent* Nearby = FindNearbyAgent();

	if (Nearby)
	{
		const FVector Away = Current - Nearby->GetActorLocation();

		Direction = (Direction + Away.GetSafeNormal() * 1.5).GetSafeNormal();
	}

	Direction = ScanAhead(Direction);

	SetActorLocation(Current + Direction * Speed * DeltaTime);
}

void ASimAgent::PickDestination()
{
	Destination = Center + FVector(FMath::FRandRange(-Radius, Radius), FMath::FRandRange(-Radius, Radius), 0.0f);
}

static bool CompareDistance(const TPair<double, ASimAgent*>& A, const TPair<double, ASimAgent*>& B)
{
	return A.Key < B.Key;
}

ASimAgent* ASimAgent::FindNearbyAgent() const
{

	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(this, ASimAgent::StaticClass(), Actors);

	TArray<TPair<double, ASimAgent*>> Distances;

	const FVector Current = GetActorLocation();

	for (AActor* Actor : Actors)
	{
		if (Actor == this)
		{
			continue;
		}

		const double Distance = FVector::DistSquared(Current, Actor->GetActorLocation());

		Distances.Emplace(Distance, static_cast<ASimAgent*>(Actor));
	}

	Distances.Sort(CompareDistance);

	if (Distances.Num() == 0)
	{
		return nullptr;
	}

	if (Distances[0].Key < 32400.0)
	{
		return Distances[0].Value;
	}

	return nullptr;
}

FVector ASimAgent::ScanAhead(const FVector& Direction) const
{
	UWorld* World = GetWorld();

	if (!World)
	{
		return Direction;
	}

	const FVector Start = GetActorLocation();
	FVector Result = Direction;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	for (int32 i = -1; i <= 1; ++i)
	{
		const FVector RayDirection = Direction.RotateAngleAxis(i * 30.0f, FVector::UpVector);

		const FVector End = Start + RayDirection * 220.0f;

		FHitResult Hit;

		if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
		{
			Result += Hit.ImpactNormal;
		}
	}

	return Result.GetSafeNormal();
}


