#include "BitBoard.h"


// TODO: change parameter from u64 array to string (FEN string) 
BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES]) : m_attackPatterns(AttackDictionary(new std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>[SIDES]))
{
    // side flag | w castle flag | wl castle flag|b castle flag| bl castle flag | en passant flag 
    this->m_moveFlags = 0b11111;

    for (int color = 0; color < SIDES; color++)
    {
        this->m_attackPatterns[color] = std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>(new std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]);
        for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
        {
            this->m_attackPatterns[color][piece] = std::shared_ptr<u64[NUMBER_OF_SQUARES]>(new u64[NUMBER_OF_SQUARES]);
            this->m_pieces[color][piece] = pieces[color][piece];
        }
    }

    for (int square = 0; square < NUMBER_OF_SQUARES; square++)
    {
        u64 attack = 0ULL;
        this->m_attackPatterns[WHITE][pawn][square] = BitBoard::calcWhitePawnAtkPattern(square);
        this->m_attackPatterns[BLACK][pawn][square] = BitBoard::calcBlackPawnAtkPattern(square);

        attack = BitBoard::calcKnightAtkPattern(square);
        this->m_attackPatterns[WHITE][knight][square] = attack;
        this->m_attackPatterns[BLACK][knight][square] = attack;

        attack = BitBoard::calcBishopAtkPattern(square);
        this->m_attackPatterns[WHITE][bishop][square] = attack;
        this->m_attackPatterns[BLACK][bishop][square] = attack;

        attack = BitBoard::calcKingAtkPattern(square);
        this->m_attackPatterns[WHITE][king][square] = attack;
        this->m_attackPatterns[BLACK][king][square] = attack;

        attack = BitBoard::calcRookAtkPattern(square);
        this->m_attackPatterns[WHITE][rook][square] = attack;
        this->m_attackPatterns[BLACK][rook][square] = attack;

        attack = BitBoard::calcQueenAtkPattern(square);
        this->m_attackPatterns[WHITE][queen][square] = attack;
        this->m_attackPatterns[BLACK][queen][square] = attack;
    }
}

// Using shallow copy to avoid unnecessary computation 
BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], AttackDictionary& attackPatterns, uint8_t flags) : m_attackPatterns(attackPatterns), m_moveFlags(flags)
{
    for (int color = 0; color < SIDES; color++)
    {
        for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
        {
            this->m_pieces[color][piece] = pieces[color][piece];
        }
    }
}


/*
* Method for playing a move. Instead of changing the current bitboard it generates a new 
* bitboard with an updated state
* input: start and end square of move
* output: bitboard after move was played
*/
std::unique_ptr<BitBoard> BitBoard::move(int startSquare, int endSquare)
{
    int piece = 0;
    bool color = this->m_moveFlags & 0b1;
    u64 startPos = 0ULL;
    u64 endPos = 0ULL;

    SET_BIT(startPos, startSquare);
    SET_BIT(endPos, endSquare);
    u64 currColorBoard = color ? getWhiteOccupancy() : getBlackOccupancy();
    
    if (!(startPos & currColorBoard))
    {
        throw MissingPieceException(startSquare, color);
    }
    piece = getPieceType(startSquare, color);

    if (!(this->m_attackPatterns[color][piece][startSquare] & endPos))
    {
        throw IllegalMoveException();
    }




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
* input: Color and piece index of the board (int, int)
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
* Method for finding which piece is on the given square
* input: square a piece is on
* output: piece identifier value (int)
*/
int BitBoard::getPieceType(int square, bool color)
{
    u64 board = 0ULL;
    SET_BIT(board, square);
    int piece = 0;

    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        if (board & this->m_pieces[color][i])
        {
            piece = i;
            break;
        }
    }
    return piece;
}


/*
* Method for getting the index of the least significant bit (LSB) in a given
* bitboard
* input: bitboard (u64)
* output: index of LSB in given board
*/
int BitBoard::getLsbIndex(u64 board)
{
    if (!board)
    {
        return -1;
    }
    return this->bitCount((board & -board) - 1);
}


/*
* Method for checking if the king is in check
* input: None
* output: true if the king is in check, false otherwise.
*/
bool BitBoard::isCheck()
{
    bool color = this->m_moveFlags & 0b1;
    return this->m_pieces[color][king] & this->getAttackSqrs(color);
}

/*
* Method to get the occupancy board defined as a single bitboard that represents 
* the location of all the pieces without distingushing piece type
* input: None
* output: a occupancy bitboard that contains all the pieces (u64) 
*/
u64 BitBoard::getOccupancy() const
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
* Method to get the white occupancy board with the location of all white pieces
* input: None
* output: a occupancy bitboard that contains all white pieces (u64)
*/
u64 BitBoard::getWhiteOccupancy() const
{
    u64 unifiedBoard = 0ULL;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        unifiedBoard |= this->m_pieces[WHITE][i];
    }
    return unifiedBoard;
}


/*
* Method to get the black occupancy board with the location of all black pieces
* input: None
* output: a occupancy bitboard that contains all black pieces (u64)
*/
u64 BitBoard::getBlackOccupancy() const
{
    u64 unifiedBoard = 0ULL;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        unifiedBoard |= this->m_pieces[BLACK][i];
    }
    return unifiedBoard;
}

/*
* Method for getting all the attacked squares of a given side on the board
* input: side (white|black) (bool)
* output: bitboard of all attacked squares (u64)
*/
u64 BitBoard::getAttackSqrs(const bool side)
{
    u64 attack = 0ULL;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        u64 board = this->m_pieces[side][i];
        while (board)
        {
            int index = getLsbIndex(board);
            u64 pattern = this->m_attackPatterns[side][i][index];
            if (i == bishop) { pattern = this->removeBishopBlockedAtk(index, pattern); }
            else if (i == rook) { pattern = this->removeRookBlockedAtk(index, pattern); }
            else if (i == queen) { pattern = this->removeQueenBlockedAtk(index, pattern); }

            attack |= pattern;
            board &= board - 1;
        }
    }
    return attack;
}


/*
* Method for removing blocked attack squares from a bishop attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeBishopBlockedAtk(int square, u64 atk)
{
    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;
    bool isBlocked = false;
    u64 occupied = this->getOccupancy();

    // bishop moving shl 9
    for (r = rank + 1, f = file + 1, isBlocked = false; r <= 7 && f <= 7; r++, f++)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & occupied;
    }

    // bishop moving shr 9
    for (r = rank + -1, f = file - 1, isBlocked = false; r >= 0 && f >= 0; r--, f--)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & occupied;
    }

    // bishop moving shr 7
    for (r = rank - 1, f = file + 1, isBlocked = false; r >= 0 && f <= 7; r--, f++)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & occupied;
    }

    // bishop moving shl 7
    for (r = rank + 1, f = file - 1, isBlocked = false; r <= 7 && f >= 0; r++, f--)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & occupied;
    }

    return atk;
}


/*
* Method for removing blocked attack squares from a rook attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeRookBlockedAtk(int square, u64 atk)
{
    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;
    bool isBlocked = false;
    u64 occupied = this->getOccupancy();

    // rook shl 8
    for (r = rank + 1, isBlocked = false; r <= 7; r++)
    {
        if(isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + file));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + file)) & occupied;

    }

    // rook shr 8
    for (r = rank - 1, isBlocked = false; r >= 0; r--)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + file));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + file)) & occupied;
    }

    // rook shl 1
    for (f = file + 1, isBlocked = false; f <= 7; f++)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((rank * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((rank * 8) + f)) & occupied;
    }

    // rook shr 1
    for (f = file - 1, isBlocked = false; f >= 0; f--)
    {
        if (isBlocked)
        {
            atk ^= (1ULL << ((rank * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((rank * 8) + f)) & occupied;
    }

    return atk;
}


/*
* Method for removing blocked attack squares from a queen attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeQueenBlockedAtk(int square, u64 atk)
{
    return this->removeBishopBlockedAtk(square, atk) | this->removeRookBlockedAtk(square, atk);
}


/*
* Method for counting the bits in a bitboard
* input: board to count the bits of (u64)
* output: number of set bits in input board (int)
*/
inline int BitBoard::bitCount(u64 board)
{
    int count = 0;
    while (board)
    {
        board &= board - 1;
        count++;
    }
    return count;
}


/*
* Method for calculating the king attack patterns
* input: square the king is on (int)
* output: king attack pattern (u64)
*/
u64 BitBoard::calcKingAtkPattern(int square)
{
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
        attack = attack & (hFileMask ^ ULLONG_MAX);
    }
    else if (board & hFileMask)
    {
        attack = attack & (aFileMask ^ ULLONG_MAX);
    }
    return attack;
}

/*
* Method for calculating the knights attack pattern
* input: square the knight is on (int)
* output: knight attack pattern (u64)
*/
u64 BitBoard::calcKnightAtkPattern(int square)
{
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
        attack = attack & (hgFileMask ^ ULLONG_MAX);
    }
    else if (board & hgFileMask)
    {
        attack = attack & (abFileMask ^ ULLONG_MAX);
    }
    return attack;
}


/*
* Method for calculating the black pawn attack patterns
* input: square the pawn is on (int)
* output: pawn attack pattern (u64)
*/
u64 BitBoard::calcBlackPawnAtkPattern(int square)
{
    if (square >= a1) // if the black pawn is on the 1st rank
    {
        return 0ULL;
    }

    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for the  H file
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for the  A file

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
* input: square the bishop is on (int)
* output: bishop attack pattern (u64)
*/
u64 BitBoard::calcBishopAtkPattern(int square)
{
    u64 board = 0ULL;
    SET_BIT(board, square);
    u64 attack = 0ULL;

    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;

    // bishop moving shl 9
    for(r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shr 9
    for(r = rank + -1, f = file - 1; r >= 0 && f >= 0; r--, f--)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shr 7
    for(r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shl 7
    for(r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--)
    { attack |= (1ULL << ((r * 8) + f)); }
    
    return attack;
}


/*
* Method for calculating the rook attack pattern
* input: square the rook is on (int)
* output: rook attack pattern (u64)
*/
u64 BitBoard::calcRookAtkPattern(int square)
{
    u64 board = 0ULL;
    SET_BIT(board, square);
    u64 attack = 0ULL;

    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;

    // rook shl 8
    for (r = rank + 1; r <= 7; r++)
    { attack |= (1ULL << ((r * 8) + file)); }

    // rook shr 8
    for (r = rank -1; r >= 0; r--)
    { attack |= (1ULL << ((r * 8) + file)); }

    // rook shl 1
    for (f = file + 1; f <= 7; f++)
    { attack |= (1ULL << ((rank * 8) + f)); }

    // rook shr 1
    for (f = file - 1;f >= 0; f--)
    { attack |= (1ULL << ((rank * 8) + f)); }

    return attack;
}


/*
* Method for calculating the queen attack pattern
* input: square the queen is on (int)
* output: queen attack pattern (u64)
*/
u64 BitBoard::calcQueenAtkPattern(int square)
{
    return calcBishopAtkPattern(square) | calcRookAtkPattern(square);
}


/*
* Method for calculating the white pawn attack pattern
* input: square the pawn is on (int)
* output: pawn attack pattern (u64)
*/
u64 BitBoard::calcWhitePawnAtkPattern(int square)
{
    if (square <= h8) // if the white pawn is on the 8th rank
    {
        return 0ULL;
    }
    
    constexpr u64 hFileMask = 9259542123273814144ULL; // mask for the  H file
    constexpr u64 aFileMask = 72340172838076673ULL; // mask for the  A file

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
