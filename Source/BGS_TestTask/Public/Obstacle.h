#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UBoxComponent;

UCLASS()
class BGS_TESTTASK_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	int GetScoreForOvercomingObstacle();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> mesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UBoxComponent> obstacleOvercomeDetector;
	UPROPERTY(EditDefaultsOnly) int scoreForOvercomingObstacle;
};
