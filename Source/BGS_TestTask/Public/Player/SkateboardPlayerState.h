#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SkateboardPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerScoreChangedDelegate, int, newScore);

UCLASS()
class BGS_TESTTASK_API ASkateboardPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure) int GetPlayerScore() const;
	void AddPlayerScore(int scoreToAdd);

	UPROPERTY(BlueprintAssignable) FPlayerScoreChangedDelegate OnPlayerScoreChangedEvent;

protected:
	virtual void BeginPlay() override;
	
private:
	int playerScore;
};
