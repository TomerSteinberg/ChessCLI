#include "Context.h"

Context::Context()
{
	this->m_currGame = nullptr;
}


Game* Context::getCurrGame() const
{
	return this->m_currGame;
}

void Context::newGame(Game* game)
{
	this->m_currGame = game;
}

void Context::deleteGame()
{
	if (this->m_currGame != nullptr)
	{
		delete this->m_currGame;
	}
}
