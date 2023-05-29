#include "BitBoard.h"


BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES])
{
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            this->_pieces[i][j] = pieces[i][j];
        }
    }
}


IBoard* BitBoard::move(std::string startPos, std::string endPos)
{
    return nullptr;
}

std::string BitBoard::getFEN()
{
    return std::string();
}


void BitBoard::printBoard()
{

}


void BitBoard::printBoardUnicode()
{
}


u64 BitBoard::getUnifiedBoard()
{
    u64 unifiedBoard = 0ULL;
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            unifiedBoard |= this->_pieces[i][j];
        }
    }
    return unifiedBoard;
}
