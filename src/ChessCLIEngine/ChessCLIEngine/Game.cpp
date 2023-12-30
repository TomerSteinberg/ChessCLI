#include "Game.h"

Game::Game(std::string fen)
{
	this->m_moves.push_back(std::make_shared<BitBoard>(fen));
	this->m_currPosition = *m_moves.begin();
}

void Game::showPosition(bool isUnicode) const
{
	this->m_currPosition->printBoard(isUnicode);
	std::cout << std::endl;
}

/*
* Plays a move on the boards and adds the result to the move history
* input: start square, end square and promotion piece
* output: none
*/
void Game::move(int startSquare, int endSquare, int promotionPiece, std::string moveNotation)
{
	std::shared_ptr<BitBoard> newPosition = this->m_currPosition->move(startSquare, endSquare, promotionPiece);
	this->m_moves.push_back(newPosition);
	this->m_currPosition = this->m_moves.back();
	if (moveNotation != "")
	{
		this->moveHistory.push_back(moveNotation);
	}
}

void Game::move(bool isLongCastle, std::string moveNotation)
{
	std::shared_ptr<BitBoard> newPosition = this->m_currPosition->castleMove(isLongCastle);
	this->m_moves.push_back(newPosition);
	this->m_currPosition = this->m_moves.back();
	if (moveNotation != "")
	{
		this->moveHistory.push_back(moveNotation);
	}
}

std::string Game::getFen() const
{
	return this->m_currPosition->getFen();
}

std::vector<std::string> Game::getAllFen() const
{
	std::vector<std::string> fenStrings;
	for (auto it = this->m_moves.begin(); it != this->m_moves.end(); it++)
	{
		fenStrings.push_back(it->get()->getFen());
	}
	return fenStrings;
}

std::vector<std::string> Game::getHistory() const
{
	return this->moveHistory;
}
