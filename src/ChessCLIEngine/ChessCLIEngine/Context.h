#pragma once
#include "Game.h"

class Context
{
public:
	Context();

	Game* getCurrGame() const;
	void newGame(Game* game);
	void deleteGame();


private:
	Game* m_currGame;
};

