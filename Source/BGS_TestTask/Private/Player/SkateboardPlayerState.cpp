#include "Player/SkateboardPlayerState.h"

void ASkateboardPlayerState::BeginPlay()
{
	Super::BeginPlay();

	playerScore = 0;
}


int ASkateboardPlayerState::GetPlayerScore() const
{
	return playerScore;
}

void ASkateboardPlayerState::AddPlayerScore(int scoreToAdd)
{
	if(scoreToAdd <= 0) return;

	playerScore += scoreToAdd;
	OnPlayerScoreChangedEvent.Broadcast(playerScore);
}

