#include "Game.h"

Game::Game(std::string fen)
{
	this->m_moves.push_back(std::make_shared<BitBoard>(fen));
	this->m_currPosition = *m_moves.begin();
}

void Game::showPosition(bool isUnicode)
{
	this->m_currPosition->printBoard(isUnicode);
	std::cout << std::endl;
}
