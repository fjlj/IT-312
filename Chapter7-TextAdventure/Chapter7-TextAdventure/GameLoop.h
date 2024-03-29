#pragma once

#include "Player.h"
#include "PlayerOptions.h"

class Game
{
private:
	Player m_player;

	void WelcomePlayer();
	void GetPlayerConsolePref();	//add function prototype to the Game class definition
	void GivePlayerOptions() const;
	void GetPlayerInput(std::string& playerInput) const;
	PlayerOptions EvaluateInput(std::string& playerInput) const;
public:

	void RunGame();
};