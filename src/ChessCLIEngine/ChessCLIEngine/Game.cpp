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


/*
* Gets Optional PseudoLegal moves
* input: None
* output: vector of move strings
*/
std::vector<std::string> Game::getOptions() const
{
	std::vector<std::string> continuations;
	std::deque<Move> options = this->m_currPosition->getMoveList();
	for (auto it = options.begin(); it != options.end(); it++)
	{
		continuations.push_back(notationFromMove(*it));
	}
	return continuations;
}


/*
* Gets the notation from a Move object
* input: Move object
* output: string of move notation
*/
std::string Game::notationFromMove(Move move) const
{
	if (move.isLong)
	{
		return "0-0-0";
	}
	if (move.castle && !move.isLong)
	{
		return "0-0";
	}
	std::string from = std::to_string(BitBoard::getLsbIndex(move.from) % 8);
	std::string to = std::to_string(BitBoard::getLsbIndex(move.to) % 8);
	from[0] += 49;
	to[0] += 49;
	from += std::to_string(8 - (BitBoard::getLsbIndex(move.from) / 8));
	to += std::to_string(8 - (BitBoard::getLsbIndex(move.to) / 8));
	std::string continuation = from + to;
	if (move.promotion != NO_PROMOTION)
	{
		switch (move.promotion)
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
	return continuation;
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

/*
* Evaluates the current position using minimax
* input: None TODO: add depth parameter
* output: score of current position
*/
int Game::evaluate()
{
	return MoveSearch::minimax(m_currPosition, (m_currPosition->getFlags() & 0b1), SEARCH_DEPTH);
}


/*
* Finds and prints the best moves in the current position
* input: None. TODO: add support for depth parameter
* output: None
*/
void Game::analyze()
{
	std::deque<Move> moves = this->m_currPosition->getMoveList();
	std::deque<std::pair<Move, double>> bestScores;
	Move bestMove = { 0,0,NO_PROMOTION, false, false };
	bool color = this->m_currPosition->getFlags() & 0b1;

	for (std::deque<Move>::iterator it = moves.begin(); it != moves.end(); it++)
	{
		std::shared_ptr<BitBoard> nextPosition;
		double score = 0;
		try
		{
			if (!it->castle)
			{
				nextPosition = this->m_currPosition->move(
					BitBoard::getLsbIndex(it->from),
					BitBoard::getLsbIndex(it->to),
					it->promotion);
			}
			else
			{
				nextPosition = this->m_currPosition->castleMove(it->isLong);
			}
		}
		catch (...)
		{
			continue;
		}

		score = MoveSearch::minimax(nextPosition, (nextPosition->getFlags() & 0b1), SEARCH_DEPTH);
		bestScores.push_back({ *it, score });
	}
	std::sort(bestScores.begin(), bestScores.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (int i = 0; i < 5; i++)
	{
		const auto& move = color ? bestScores.back() : bestScores.front();

		std::cout << i + 1 << ".\t" << notationFromMove(move.first) << "\t"
			<< move.second / 1000 << std::endl;
		color ? bestScores.pop_back() : bestScores.pop_front();
	}
}


/*
* Play the best computer continuation to the current position
* input: None. TODO: add depth parameter
* output: None
*/
void Game::playBest()
{
	std::deque<Move> moves = this->m_currPosition->getMoveList();
	Move bestMove = { 0,0,NO_PROMOTION, false, false };
	bool color = this->m_currPosition->getFlags() & 0b1;
	double bestScore = color ? MIN_INFINITY : MAX_INFINITY;
	for (std::deque<Move>::iterator it = moves.begin(); it != moves.end(); it++)
	{
		std::shared_ptr<BitBoard> nextPosition;
		double score = 0;
		try
		{
			if (!it->castle)
			{
				nextPosition = this->m_currPosition->move(
					BitBoard::getLsbIndex(it->from),
					BitBoard::getLsbIndex(it->to),
					it->promotion);
			}
			else
			{
				nextPosition = this->m_currPosition->castleMove(it->isLong);
			}
		}
		catch (...)
		{
			continue;
		}

		score = MoveSearch::minimax(nextPosition, (nextPosition->getFlags() & 0b1), SEARCH_DEPTH);
		if (color)
		{
			bestScore = score >= bestScore ? score : bestScore;
			bestMove = score >= bestScore ? *it : bestMove;
		}
		else
		{
			bestScore = score <= bestScore ? score : bestScore;
			bestMove = score <= bestScore ? *it : bestMove;
		}
	}
	this->move(BitBoard::getLsbIndex(bestMove.from),
		BitBoard::getLsbIndex(bestMove.to),
		bestMove.promotion, notationFromMove(bestMove));
}


/*
* Dump of current position
* input: Pieces array
* output: flags and enpassant dump (side effect on pieces array)
*/
std::pair<uint8_t, uint8_t> Game::dump(u64 pieces[SIDES][NUMBER_OF_PIECES])
{
	this->m_currPosition->getPiecesCopy(pieces);
	return { this->m_currPosition->getFlags(), this->m_currPosition->getEnPassant() };
}
