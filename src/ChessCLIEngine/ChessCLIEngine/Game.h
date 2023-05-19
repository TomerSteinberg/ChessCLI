#pragma once
#include "Position.h"
#include <list>
#include <string>


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

