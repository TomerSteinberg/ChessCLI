#include "Context.h"

Context::Context()
{
	this->m_inGame = false;
}

bool Context::getInGame() const
{
	return this->m_inGame;
}

void Context::setInGame(const bool val)
{
	this->m_inGame = val;
}
