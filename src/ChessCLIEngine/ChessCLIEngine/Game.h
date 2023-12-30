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
	
	void showPosition(bool isUnicode=false) const;
	void move(int startSquare, int endSquare, int promotionPiece,std::string moveNotation = "");
	void move(bool isLongCastle, std::string moveNotation = "");
	std::string getFen() const;
	std::vector<std::string> getAllFen() const;
	std::vector<std::string> getHistory() const;

private:
	std::list<std::shared_ptr<BitBoard>> m_moves;
	std::vector<std::string> moveHistory;
	std::shared_ptr<BitBoard> m_currPosition;

};

#endif