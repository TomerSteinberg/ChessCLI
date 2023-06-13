#include "BitBoard.h"


BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES])
{
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            this->m_pieces[i][j] = pieces[i][j];
        }
    }
    // TODO: Calculate piece attack patterns
}


BitBoard::BitBoard()
{
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            for (int k = 0; k < NUMBER_OF_SQUARES; k++)
            {
                this->m_attackPatterns[i][j][k] = 0ULL;
            }
            this->m_pieces[i][j] = 0ULL;
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


/*
* Method for printing a specific bitBoard in the chess board
* input: Color and piece index of the board
* output: None
*/
void BitBoard::printPieceBitBoard(int color, int piece)
{
    if (piece >= NUMBER_OF_PIECES || color >= SIDES || piece < 0 || color < 0)
    {
        return;
    }
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        std::cout << BOARD_HEIGHT - i << " ";
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            std::cout << GET_BIT(this->m_pieces[color][piece], (i * 8) + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

/*
* Method to get the unified board defined as a single bitboard that represents 
* the location of all the pieces without distingushing piece type
* input: None
* output: a unified bitboard that contains all the pieces (u64) 
*/
u64 BitBoard::getUnifiedBoard()
{
    u64 unifiedBoard = 0ULL;
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            unifiedBoard |= this->m_pieces[i][j];
        }
    }
    return unifiedBoard;
}

u64 BitBoard::calcBlackPawnAtkPattern(int square)
{
    return u64();
}


/*
* Method for calculating the white pawn attack patterns
* input: pawn bitboard (u64)
* output: pawn attack pattern bitboard (u64)
*/
u64 BitBoard::calcWhitePawnAtkPattern(int square)
{
    if (square < 8) // if the white pawn is on the 8th rank
    {
        return 0ULL;
    }
    
    const u64 hFileMask = 9259542123273814144ULL; // mask for entire H file
    const u64 aFileMask = 72340172838076673ULL; // mask for entire A file

    u64 board = 0ULL;
    u64 attack = board;
    SET_BIT(board, square);
    if (!(board & hFileMask))
    {
        attack = board >> 7;
    }
    if (!(board & aFileMask))
    {
        attack = attack | (board >> 9);
    }
    return attack;
}
