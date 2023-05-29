#pragma once
#include <string>


class IBoard
{
public:
	virtual IBoard* move(std::string startPos, std::string endPos)=0;
	virtual std::string getFEN()=0;
	virtual void printBoard()=0;
	virtual void printBoardUnicode()=0;
};

