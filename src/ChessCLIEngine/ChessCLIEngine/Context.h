#ifndef CONTEXT_H
#define CONTEXT_H

#include "Game.h"

class Context
{
public:
	Context();

	std::shared_ptr<Game> getCurrGame() const;
	void newGame(std::string fen);
	void deleteGame();


private:
	std::shared_ptr<Game> m_currGame;
};

#endif