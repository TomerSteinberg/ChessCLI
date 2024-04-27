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
* Gets Optional Legal moves
* input: None
* output: vector of move strings
*/
std::vector<std::string> Game::getOptions() const
{
	std::vector<std::string> continuations;
	auto options = this->m_currPosition->getMoveList();
	for (int i = 0; i < options.size(); i++)
	{
		for (int j = 0; j < options[i].size(); j++)
		{
			if (options[i][j].from == options[i][j].to && !options[i][j].castle)
			{
				break;
			}
			continuations.push_back(notationFromMove(options[i][j]));
		}
	}
	return continuations;
}


/*
* Gets the notation from a Move object
* input: Move object
* output: string of move notation
*/
std::string Game::notationFromMove(Move move)
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
double Game::evaluate()
{
	return (double)(MoveSearch::minimax(m_currPosition, (m_currPosition->getFlags() & 0b1), SEARCH_DEPTH + 1)) / 1000;
}


/*
* Finds and prints the best moves in the current position
* input: None. TODO: add support for depth parameter
* output: None
*/
void Game::analyze()
{
	auto moves = this->m_currPosition->getMoveList();
	std::deque<std::pair<Move, int>> bestScores;
	Move bestMove = { 0,0,NO_PROMOTION, false, false };
	bool color = this->m_currPosition->getFlags() & 0b1;

	for (int i = 0; i < moves.size(); i++)
	{
		for (int j = 0; j < moves[i].size(); j++)
		{
			if (moves[i][j].from == moves[i][j].to && !moves[i][j].castle)
			{
				break;
			}
			std::shared_ptr<BitBoard> nextPosition;
			int score = 0;
			if (!moves[i][j].castle)
			{
				nextPosition = this->m_currPosition->move(
					BitBoard::getLsbIndex(moves[i][j].from),
					BitBoard::getLsbIndex(moves[i][j].to),
					moves[i][j].promotion);
			}
			else
			{
				nextPosition = this->m_currPosition->castleMove(moves[i][j].isLong);
			}

			score = MoveSearch::minimax(nextPosition, (nextPosition->getFlags() & 0b1), SEARCH_DEPTH);
			bestScores.push_back({ moves[i][j], score });
		}
	}
	std::sort(bestScores.begin(), bestScores.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (int i = 0; i <= bestScores.size(); i++)
	{
		const auto& move = color ? bestScores.back() : bestScores.front();

		std::cout << i + 1 << ".\t" << notationFromMove(move.first) << "\t"
			<< ((float)move.second) / 1000 << std::endl;
		color ? bestScores.pop_back() : bestScores.pop_front();
	}
}


/*
* Finds the best computer continuation to the current position
* input: Depth of search.
* output: Best continuation
*/
Move Game::searchBest(int searchDepth, std::array<Move, 128> priorityMoves)
{
	auto baseMoves = this->m_currPosition->getMoveList();
	std::array<std::array<Move, 128>, MOVE_ORDERING_CATEGORIES + 1> moves = { priorityMoves, baseMoves[killer], baseMoves[special], baseMoves[good], baseMoves[average], baseMoves[worst] };
	if (this->m_currPosition->getMoveListLength() == 0)
	{
		return { 0,0,NO_PROMOTION, false, false };
	}
	Move bestMove = { 0,0,NO_PROMOTION, false, false };
	bool color = this->m_currPosition->getFlags() & 0b1;
	int bestScore = color ? ALPHA_START : BETA_START;
	for (int i = 0; i < moves.size(); i++)
	{
		for (int j = 0; j < moves[i].size(); j++)
		{
			if (moves[i][j].from == moves[i][j].to && !moves[i][j].castle)
			{
				break;
			}
			std::shared_ptr<BitBoard> nextPosition;
			int score = 0;
			if (!moves[i][j].castle)
			{
				nextPosition = this->m_currPosition->move(
					BitBoard::getLsbIndex(moves[i][j].from),
					BitBoard::getLsbIndex(moves[i][j].to),
					moves[i][j].promotion);
			}
			else
			{
				nextPosition = this->m_currPosition->castleMove(moves[i][j].isLong);
			}

			const u64 zobristHash = nextPosition->getZobristHash();

			if (MoveSearch::transpositionTable[zobristHash].second != -1 && MoveSearch::transpositionTable[zobristHash].second >= (SEARCH_DEPTH))
			{
				score = MoveSearch::transpositionTable[zobristHash].first;
			}
			else
			{
				score = MoveSearch::minimax(nextPosition, !color, searchDepth);
				MoveSearch::transpositionTable[zobristHash] = { score, searchDepth };
			}
			if (color)
			{
				bestScore = std::max(bestScore, score);
				bestMove = score >= bestScore ? moves[i][j] : bestMove;
			}
			else
			{
				bestScore = std::min(bestScore, score);
				bestMove = score <= bestScore ? moves[i][j] : bestMove;
			}
		}
	}
	return bestMove;
}

/*
* Plays the best move using Iterative Deepening
* input: maximum depth of search
* output: None
*/
void Game::iterativeDeepening(int maxDepth)
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::array<Move, 128> priorityMoves = { {0, 0, NO_PROMOTION, false, false} };

	Move bestMove = { 0,0,NO_PROMOTION, false, false };
	for (uint8_t depth = 1; depth <= maxDepth; depth++)
	{
		auto t1 = high_resolution_clock::now();
		bestMove = searchBest(depth, priorityMoves);
		auto t2 = high_resolution_clock::now();
		auto ms_int = duration_cast<milliseconds>(t2 - t1);

		priorityMoves[depth - 1] = bestMove;
		if (bestMove.from == bestMove.to && !bestMove.castle)
		{
			std::cout << "Unable to continue. The Game is over." << std::endl;
			return;
		}
		duration<double, std::milli> ms_double = t2 - t1;
		std::cout << "Depth:\t" << (int)depth << "\tTime:\t" << ms_int.count() << "ms\t" << "Nodes:\t" << MoveSearch::nodes << "\t" << notationFromMove(bestMove) << std::endl;
		MoveSearch::nodes = 0;
	}
	if (bestMove.castle)
	{
		this->move(bestMove.isLong, notationFromMove(bestMove));
	}
	else
	{
		this->move(BitBoard::getLsbIndex(bestMove.from), BitBoard::getLsbIndex(bestMove.to),
			bestMove.promotion, notationFromMove(bestMove));
	}
}


int Game::perft(int depth)
{
	return MoveSearch::perft(this->m_currPosition, depth);
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
