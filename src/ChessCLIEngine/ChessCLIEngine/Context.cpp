#include "Context.h"

Context::Context()
{
	this->m_currGame = nullptr;
}


std::shared_ptr<Game> Context::getCurrGame() const
{
	return this->m_currGame;
}

/*
* creates a new game instance using fen string
* input: fen string of first position
* output: none
*/
void Context::newGame(std::string fen)
{
	this->m_currGame = std::make_shared<Game>(Game(fen));
}

void Context::deleteGame()
{
	this->m_currGame.reset();
	this->m_currGame = nullptr;
}
