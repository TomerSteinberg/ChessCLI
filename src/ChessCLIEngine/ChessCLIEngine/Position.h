#pragma once
#include <string>
#include "IBoard.h"


class Position
{
public:
	Position(std::string fen);
	Position* move(std::string move);


private:
	Position(Position pos, std::string move); // private constructor for making moves
	IBoard* m_board;


};

