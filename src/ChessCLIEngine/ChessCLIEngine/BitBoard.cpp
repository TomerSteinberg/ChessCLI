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


/*
* Method for calculating the king attack patterns
* input: square the king is on
* output: king attack pattern (u64)
*/
u64 BitBoard::calcKingAtkPattern(int square)
{
    constexpr u64 allSquareMask = 18446744073709551615ULL;
    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for the entire H file
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for the entire A file

    u64 board = 0ULL;
    u64 attack = board;
    SET_BIT(board, square);
       
    // king attack offsets
    attack = board >> 1;
    attack |= board << 1;
    attack |= board >> 7;
    attack |= board >> 9;
    attack |= board << 7;
    attack |= board << 9;
    attack |= board >> 8;
    attack |= board << 8;

    if (board & aFileMask)
    {
        // mask XOR fully set mask = flipping all bits 
        // removing out of bound moves 
        attack = attack & (hFileMask ^ allSquareMask);
    }
    else if (board & hFileMask)
    {
        attack = attack & (aFileMask ^ allSquareMask);
    }
    return attack;
}

/*
* Method for calculating the knights attack pattern
* input: square the knight is on
* output: knight attack pattern (u64)
*/
u64 BitBoard::calcKnightAtkPattern(int square)
{
    constexpr u64 allSquareMask = 18446744073709551615ULL;
    constexpr u64 abFileMask = 217020518514230019ULL; // Mask for both A and B files
    constexpr u64 hgFileMask = 13889313184910721216ULL; // Mask for both H and G files
    u64 board = 0ULL;
    u64 attack = 0ULL;
    SET_BIT(board, square);

    // knight attack offsets
    attack = board >> 17 | board >> 15;
    attack |= board << 17 | board << 15;
    attack |= board >> 6 | board >> 10;
    attack |= board << 6 | board << 10;

    if (board & abFileMask)
    {
        // mask XOR fully set mask = flipping all bits 
        // removing out of bound moves 
        attack = attack & (hgFileMask ^ allSquareMask);
    }
    else if (board & hgFileMask)
    {
        attack = attack & (abFileMask ^ allSquareMask);
    }
    return attack;
}


/*
* Method for calculating the black pawn attack patterns
* input: square the pawn is on
* output: pawn attack pattern (u64)
*/
u64 BitBoard::calcBlackPawnAtkPattern(int square)
{
    if (square >= a1) // if the black pawn is on the 1st rank
    {
        return 0ULL;
    }

    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for the entire H file
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for the entire A file

    u64 board = 0ULL;
    u64 attack = board;
    SET_BIT(board, square);


    if (!(board & hFileMask))
    {
        attack = board << 9;
    }
    if (!(board & aFileMask))
    {
        attack |= (board << 7);
    }
    return attack;
}


/*
* Method for calculating the bishop attack pattern
* input: square the bishop is on
* output: bishop attack pattern (u64)
*/
u64 BitBoard::calcBishopAtkPattern(int square)
{
    u64 board = 0ULL;
    SET_BIT(board, square);
    u64 attack = 0ULL;

    attack |= calcSingleBishopDirection(board, 9, true);
    attack |= calcSingleBishopDirection(board, 9, false);
    attack |= calcSingleBishopDirection(board, 7, true);
    attack |= calcSingleBishopDirection(board, 7, false);
    return attack;
}


/*
* Method for calculating the rook attack pattern
* input: square the rook is on
* output: rook attack pattern (u64)
*/
u64 BitBoard::calcRookAtkPattern(int square)
{
    u64 board = 0ULL;
    SET_BIT(board, square);
    u64 attack = 0ULL;

    attack |= calcSingleRookDirection(board, 8, true);
    attack |= calcSingleRookDirection(board, 8, false);
    attack |= calcSingleRookDirection(board, 1, true);
    attack |= calcSingleRookDirection(board, 1, false);
    return attack;
}


/*
* Method for calculating the queen attack pattern
* input: square the queen is on
* output: queen attack pattern (u64)
*/
u64 BitBoard::calcQueenAtkPattern(int square)
{
    return this->calcBishopAtkPattern(square) | this->calcRookAtkPattern(square);
}


/*
* Function to calculate a single rook direction
* input: board (initially with piece location), number of bits to shift, shr|shl
* output: full rook direction
*/
u64 BitBoard::calcSingleRookDirection(u64 board, int direction, bool isLeft)
{
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for A file
    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for H file
    constexpr u64 eigthRankMask = 255ULL; // mask for eight rank
    constexpr u64 firstRankMask = 18374686479671623680ULL; // mask for first rank
    if (!board)
        return 0ULL;
    if (board & aFileMask && direction == 1 && !isLeft)
        return 0ULL;
    if (board & hFileMask && direction == 1 && isLeft)
        return 0ULL;
    if (board & firstRankMask && direction >= 8 && isLeft)
       return 0ULL; 
    if (board & eigthRankMask && direction >= 8 && !isLeft)
        return 0ULL;

    board = isLeft ? board << direction : board >> direction;
    return calcSingleRookDirection(board, direction, isLeft) | board;
}

u64 BitBoard::calcSingleBishopDirection(u64 board, int direction, bool isLeft)
{
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for A file
    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for H file
    constexpr u64 eigthRankMask = 255ULL; // mask for eight rank
    constexpr u64 firstRankMask = 18374686479671623680ULL; // mask for first rank
    if (!board)
        return 0ULL;
    // TODO: Finish this

    board = isLeft ? board << direction : board >> direction;
    return calcSingleBishopDirection(board, direction, isLeft) | board;
}


/*
* Method for calculating the white pawn attack pattern
* input: square the pawn is on
* output: pawn attack pattern (u64)
*/
u64 BitBoard::calcWhitePawnAtkPattern(int square)
{
    if (square <= h8) // if the white pawn is on the 8th rank
    {
        return 0ULL;
    }
    
    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for the entire H file
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for the entire A file

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
