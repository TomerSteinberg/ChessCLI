#ifndef CONTEXT_H
#define CONTEXT_H

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

#endif