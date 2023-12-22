#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>
#include "BitBoard.h"
#include <exception>
#include <memory>


class BitBoard;

class Game
{
public:
	Game(std::string fen);
	
	void showPosition(bool isUnicode=false);

private:
	std::list<std::shared_ptr<BitBoard>> m_moves;
	std::shared_ptr<BitBoard> m_currPosition;

};

#endif