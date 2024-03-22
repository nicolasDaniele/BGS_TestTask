#include "Obstacle.h"
#include "Components/BoxComponent.h"

AObstacle::AObstacle()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	obstacleOvercomeDetector = CreateDefaultSubobject<UBoxComponent>("Obstacle Overcome Detector");
	obstacleOvercomeDetector->SetupAttachment(mesh);
	obstacleOvercomeDetector->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

int AObstacle::GetScoreForOvercomingObstacle()
{
	return scoreForOvercomingObstacle;
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}
