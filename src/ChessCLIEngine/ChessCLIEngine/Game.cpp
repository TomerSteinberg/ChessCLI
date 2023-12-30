#include "Game.h"

Game::Game(std::string fen)
{
	this->m_moves.push_back(std::make_shared<BitBoard>(fen));
	this->m_currPosition = *m_moves.begin();
}


/*
* Prints current position
* input: unicdoe flag (bool)
* output: None
*/
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
void Game::move(const int startSquare, const int endSquare, const int promotionPiece, std::string moveNotation)
{
	std::shared_ptr<BitBoard> newPosition = this->m_moves.back()->move(startSquare, endSquare, promotionPiece);
	this->m_moves.push_back(newPosition);
	this->m_currPosition = this->m_moves.back();
	if (moveNotation != "")
	{
		this->m_moveHistory.push_back(moveNotation);
	}
}


/*
* Makes a castle move on the board and updates move history
* input: is Long castle (bool), move notation
* output: None
*/
void Game::move(const bool isLongCastle, std::string moveNotation)
{
	std::shared_ptr<BitBoard> newPosition = this->m_currPosition->castleMove(isLongCastle);
	this->m_moves.push_back(newPosition);
	this->m_currPosition = this->m_moves.back();
	if (moveNotation != "")
	{
		this->m_moveHistory.push_back(moveNotation);
	}
}


/*
* Removes every move after the current position
* input: None
* output: None
*/
void Game::truncate()
{
	auto posIt = find(this->m_moves.begin(), this->m_moves.end(), this->m_currPosition);
	int index = distance(this->m_moves.begin(), posIt);
	if (!(index == this->m_moves.size() - 1))
	{
		this->m_moves.erase(posIt + 1, this->m_moves.end());
		this->m_moveHistory.erase(this->m_moveHistory.begin() + index, this->m_moveHistory.end());
	}
}


/*
* Gets FEN string of current position
* input: none
* output: FEN string of current position
*/
std::string Game::getFen() const
{
	return this->m_currPosition->getFen();
}


/*
* Gets all FEN strings in the game
* input: None
* output: vector of fen strings
*/
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
	return this->m_moveHistory;
}

std::vector<std::string> Game::getOptions() const
{
	std::vector<std::string> continuations;
	std::vector<Move> options = this->m_currPosition->getMoveList();
	for (auto it = options.begin(); it != options.end(); it++)
	{
		if(it->isLong) 
		{
			continuations.push_back("0-0-0");
			continue;
		}
		if (it->castle && !it->isLong)
		{
			continuations.push_back("0-0");
			continue;
		}
		std::string from = std::to_string(BitBoard::getLsbIndex(it->from) % 8);
		std::string to = std::to_string(BitBoard::getLsbIndex(it->to) % 8);
		from[0] += 49;
		to[0] += 49;
		from += std::to_string(8 - (BitBoard::getLsbIndex(it->from) / 8));
		to += std::to_string(8 - (BitBoard::getLsbIndex(it->to) / 8));
		std::string continuation = from + to;
		if (it->promotion != NO_PROMOTION)
		{
			switch (it->promotion)
			{
			case queen:
				continuation += "q";
				break;
			case bishop:
				continuation += "b";
				break;
			case rook:
				continuation += "r";
				break;
			case knight:
				continuation += "n";
				break;
			}
		}
		continuations.push_back(continuation);

	}
	return continuations;
}

/*
* Changes current position to given index in move history
* input: index of desired positon
* output: true if index was valid and false otherwise
*/
bool Game::toPosition(const int index)
{
	if (index < this->m_moves.size() && index >= 0)
	{
		this->m_currPosition = this->m_moves[index];
		return true;
	}
	return false;
}

void Game::back()
{
	auto posIt = find(this->m_moves.begin(), this->m_moves.end(), this->m_currPosition);
	int index = distance(this->m_moves.begin(), posIt);
	if (index > 0)
	{
		this->m_currPosition = this->m_moves[index - 1];
	}
}

void Game::next()
{
	auto posIt = find(this->m_moves.begin(), this->m_moves.end(), this->m_currPosition);
	int index = distance(this->m_moves.begin(), posIt);
	if (index < (this->m_moves.size() - 1))
	{
		this->m_currPosition = this->m_moves[index + 1];
	}
}
