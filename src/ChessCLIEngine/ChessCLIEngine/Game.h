#pragma once
#include <list>
#include <string>
#include "BitBoard.h"

#define DEFAULT_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class Game
{
public:
	Game(std::string fen);
	Game();



private:
	std::list<std::shared_ptr<BitBoard>> m_moves;
	std::shared_ptr<BitBoard> m_currPosition;


};

