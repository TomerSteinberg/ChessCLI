#pragma once
#include <list>
#include <string>
#include "IBoard.h"


#define DEFAULT_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class Game
{
public:
	Game(std::string fen);
	Game();



private:
	std::list<IBoard*> m_moves;
	IBoard* m_currPosition;


};

