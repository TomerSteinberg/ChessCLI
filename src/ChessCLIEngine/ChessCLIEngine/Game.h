#pragma once
#include "Position.h"
#include <list>
#include <string>


#define DEFAULT_STARTING_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class Game
{
public:
	Game(std::string fen);
	Game(std::string pgnPath);
	Game();



private:
	std::list<Position*> m_moves;
	Position* m_currPosition;


};

