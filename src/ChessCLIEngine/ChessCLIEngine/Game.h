#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>
#include "BitBoard.h"
#include <exception>
#include <memory>
#include <algorithm>



class BitBoard;

class Game
{
public:
	Game(std::string fen);
	
	void showPosition(bool isUnicode=false) const;
	void move(const int startSquare, const int endSquare, const int promotionPiece,std::string moveNotation = "");
	void move(const bool isLongCastle, std::string moveNotation = "");
	void truncate();
	bool toPosition(const int index);
	void back();
	void next();
	std::pair<uint8_t, uint8_t> dump(u64 pieces[SIDES][NUMBER_OF_PIECES]);
	std::string getFen() const;
	std::vector<std::string> getAllFen() const;
	std::vector<std::string> getHistory() const;
	std::vector<std::string> getOptions() const;

private:
	std::vector<std::shared_ptr<BitBoard>> m_moves;
	std::vector<std::string> m_moveHistory;
	std::shared_ptr<BitBoard> m_currPosition;

};

#endif