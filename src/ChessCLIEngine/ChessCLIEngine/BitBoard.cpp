#include "BitBoard.h"
#include "Parser.h"
#include <Windows.h>


BitBoard::BitBoard(std::string fen) : m_attackPatterns(AttackDictionary(new std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>[SIDES]))
{
    this->m_enPassantSquare = NO_ENPASSANT;
    this->m_moveFlags = 0b0;

    for (int color = 0; color < SIDES; color++)
    {
        // attack pattern memory allocation
        this->m_attackPatterns[color] = std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>(new std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]);
        for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
        {
            this->m_attackPatterns[color][piece] = std::shared_ptr<u64[NUMBER_OF_SQUARES]>(new u64[NUMBER_OF_SQUARES]);
            this->m_pieces[color][piece] = 0ULL; // reseting pieces
        }
    }

    parseFen(fen);
    initAtkDictionary();

    this->m_whiteOccupancy = getSideOccupancy(WHITE);
    this->m_blackOccupancy = getSideOccupancy(BLACK);
    this->m_whiteMoveList = getPseudoLegalMoves(WHITE);
    this->m_blackMoveList = getPseudoLegalMoves(BLACK);
    this->m_whiteAtkedSqrs = getAttackSqrs(WHITE);
    this->m_blackAtkedSqrs = getAttackSqrs(BLACK);
}


// Using shallow copy for attack dictionary to avoid unnecessary computation 
BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], const AttackDictionary& attackPatterns, uint8_t flags, uint8_t enPassant) :
    m_attackPatterns(attackPatterns), m_enPassantSquare(enPassant) ,m_moveFlags(flags)
{
    for (int color = 0; color < SIDES; color++)
    {
        for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
        {
            this->m_pieces[color][piece] = pieces[color][piece];
        }
    }

    this->m_whiteOccupancy = getSideOccupancy(WHITE);
    this->m_blackOccupancy = getSideOccupancy(BLACK);
    this->m_whiteMoveList = getPseudoLegalMoves(WHITE);
    this->m_blackMoveList = getPseudoLegalMoves(BLACK);
    this->m_whiteAtkedSqrs = this->getAttackSqrs(WHITE);
    this->m_blackAtkedSqrs = this->getAttackSqrs(BLACK);
}


/*
* Evaluates the current position
* input: None
* output: Evaluation number (double)
*/
int BitBoard::evaluate() const
{
    const std::vector<int> PIECE_VALUES = { 1, 3, 3, 5, 9 };
    int evaluation = 0;
    bool color = COLOR;
    for (int i = 0; i < NUMBER_OF_PIECES - 1; i++)
    {
        evaluation += (bitCount(this->m_pieces[color][i]) * PIECE_VALUES[i]) 
                      - (bitCount(this->m_pieces[!color][i]) * PIECE_VALUES[i]);
    }
    return evaluation;
}


/*
* Method for playing a move. Instead of changing the current bitboard it generates a new 
* bitboard with an updated state
* input: start and end square of move, promotion piece
* output: bitboard after move was played
*/
std::shared_ptr<BitBoard> BitBoard::move(int startSquare, int endSquare, int promotionPiece) const
{
    if (startSquare == endSquare) { throw IllegalMoveException(); }

    int target = NO_CAPTURE;
    int piece = 0;
    const bool color = COLOR;
    u64 startPos = 0ULL, endPos = 0ULL;
    u64 nextPosition[SIDES][NUMBER_OF_PIECES] = { 0ULL };
    uint8_t nextFlags = this->m_moveFlags, nextEnPasssant = NO_ENPASSANT;
    const u64 promotionMask = this->getPromotionMask(color);
    bool isAttackingEnPassant = false;

    if( promotionPiece >= king || (promotionPiece < knight && promotionPiece != NO_PROMOTION))
    { throw IllegalMoveException("Invalid Promotion: You can only promote to Knight, Bishop, Rook or Queen."); }

    this->getPiecesCopy(nextPosition);
    SET_BIT(startPos, startSquare);
    SET_BIT(endPos, endSquare);
    u64 currColorBoard = color ? this->m_whiteOccupancy : this->m_blackOccupancy;
    u64 fullOccupancy = this->m_whiteOccupancy | this->m_blackOccupancy;

    if (!(startPos & currColorBoard)) { throw MissingPieceException(startSquare, color); }
    if (endPos & currColorBoard) { throw IllegalMoveException("You can't capture your own pieces"); }

    piece = getPieceType(startSquare, color);
    if(!isMovePseudoLegal(startSquare, endSquare, color))
    {   throw IllegalMoveException(); }

    if (piece == king) { nextFlags &= color ? 0b1111001 : 0b1100111; } // taking ability to castle
    else if (piece == rook) 
    {
        // taking ability to castle
        if (color) { nextFlags &= startSquare % 8 == 0 ? 0b1111011 : 0b1111101; }
        else { nextFlags &= startSquare % 8 == 0 ? 0b1101111 : 0b1110111; }
    }
    else if (piece == pawn)
    {
        u64 enPassantBoard = this->getEnPassantPattern(startSquare, color);
        if (endPos & enPassantBoard) { isAttackingEnPassant = true; target = pawn; }
        if (abs(startSquare - endSquare) == PAWN_DOUBLE_JUMP_DIFFERENCE)
        { nextEnPasssant = color ? endSquare + 8 : endSquare - 8; }

        if(endPos & promotionMask && promotionPiece == NO_PROMOTION)
        { throw IllegalMoveException("You didn't specify the promotion piece. i.e \"move e7e8q\" "); }
        if(!(endPos & promotionMask) && promotionPiece != NO_PROMOTION)
        { throw IllegalMoveException("You can't promote on this square"); }
    }

    if (piece != pawn && promotionPiece != NO_PROMOTION) { throw IllegalMoveException(); }
    if (endPos & fullOccupancy)
    {
        target = this->getPieceType(endSquare, !color);
    }
    
    expressMove(nextPosition, color, piece, target, startSquare, endSquare, promotionPiece);
    if (target != NO_CAPTURE) 
    {
        if (target == rook && endPos & CORNERS) // removing rook castling after getting captured
        { nextFlags ^= (2 << (color * 2) << (endPos & LEFT_CORNERS ? 1 : 0)); }

        if (isAttackingEnPassant)  // removing en Passant pawn based on color
        { endSquare = color ? endSquare + 8 : endSquare - 8; }
    } 
    return createNextPosition(nextPosition, nextFlags, nextEnPasssant);
}


/*
 * Method to get a FEN representation of the position
 * input: None
 * output: FEN representation
*/
std::string BitBoard::getFen() const
{
    std::string enPassant = "";
    std::string fen = "";
    u64 whiteOccupancy = this->m_whiteOccupancy;
    u64 fullOccupancy = this->m_whiteOccupancy | this->m_blackOccupancy;
    int unOccupied = 0;
    bool isCastleAllowed = false;
    std::unordered_map<int, char> pieceToChar = {
        {pawn, 'P'},
        {knight, 'N'},
        {bishop, 'B'},
        {rook, 'R'},
        {queen, 'Q'},
        {king, 'K'},
    };

    for (int square = 0; square < NUMBER_OF_SQUARES; square++)
    {
        u64 board = 0ULL;
        SET_BIT(board, square);
        if (!(board & fullOccupancy) && (square + 1) % 8 == 0)
        {
            fen += std::to_string(unOccupied + 1);
            fen += '/';
            unOccupied = 0;
            continue;
        }
        if (!(board & fullOccupancy))
        {
            unOccupied++;
            continue;
        }
        if (board & fullOccupancy)
        {
            if (unOccupied != 0)
            {
                fen += std::to_string(unOccupied);
                unOccupied = 0;
            }
            fen += board & whiteOccupancy ? pieceToChar[getPieceType(square, WHITE)]
                : (pieceToChar[getPieceType(square, BLACK)] + LOWER_CASE_ASCII_DIFFERENCE);
            if ((square + 1) % 8 == 0) { fen += '/'; }
        }
    }
    if (fen[fen.length() - 1] == '/') { fen.pop_back(); }

    fen += COLOR ? " w " : " b ";
    if (this->m_moveFlags & 0b10) { fen += 'K'; isCastleAllowed = true; }
    if (this->m_moveFlags & 0b100) { fen += 'Q'; isCastleAllowed = true;}
    if (this->m_moveFlags & 0b1000) { fen += 'k'; isCastleAllowed = true;}
    if (this->m_moveFlags & 0b10000) { fen += 'q'; isCastleAllowed = true;}
    if (!isCastleAllowed) { fen += '-'; }

    enPassant = std::to_string(this->m_enPassantSquare % 8);
    enPassant[0] += 49;
    enPassant += std::to_string(8 - (this->m_enPassantSquare / 8));
    fen += m_enPassantSquare == NO_ENPASSANT ? " - " : (" " + enPassant + " ");

    return fen;
}

std::vector<Move> BitBoard::getMoveList()
{
    return COLOR ? this->m_whiteMoveList : this->m_blackMoveList;
}


/*
* Method for printing a Chess board with either letters or unicode characters
* Input: isUnicode - flag for which printing type
* Output: None
*/
void BitBoard::printBoard(bool isUnicode) const
{
    std::unordered_map<int, std::vector<std::wstring>> printMap = { 
        {-1, {L"."}}, // empty square
        {pawn, {L"P", L"p", L"\u265F", L"\u2659"}},
        {knight, {L"N", L"n", L"\u265E", L"\u2658"}},
        {bishop, {L"B", L"b", L"\u265D", L"\u2657"}},
        {rook, {L"R", L"r", L"\u265C", L"\u2656"}},
        {queen, {L"Q", L"q", L"\u265B", L"\u2655"}},
        {king, {L"K", L"k", L"\u265A", L"\u2654"}}
    };

    int piece = -1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        std::cout << BOARD_HEIGHT - i << " ";
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            int printType = isUnicode ? 2 : 0;
            piece = this->getPieceType((i * 8) + j, WHITE);
            if (piece == -1) 
            {
                piece = this->getPieceType((i * 8) + j, BLACK); 
                if (piece != -1) { printType += 1; }
                else { printType = 0; }
            }
            WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                printMap[piece][printType].c_str(),
                printMap[piece][printType].size(),
                nullptr, nullptr);
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h" << std::endl;
}


/*
* Method for creating a new position based on the next position of pieces and the various flags
* input: next position board (u64[][]), flags for the position (uint8_t), next enPassant square (uint8_t)
* output: shared ptr of next position (shared_ptr<BitBoard>)
*/
std::shared_ptr<BitBoard> BitBoard::createNextPosition(u64 nextPos[SIDES][NUMBER_OF_PIECES], uint8_t nextFlags, uint8_t nextEnPassant) const
{
    bool color = COLOR;
    nextFlags ^= 0b1; // changing color turn
    // creating the instance of the next position
    std::shared_ptr<BitBoard> afterMove = std::make_shared<BitBoard>(nextPos, this->m_attackPatterns, nextFlags, nextEnPassant);

    if (this->isCheck(color) && afterMove->isCheck(color)) { throw IllegalMoveException("You're in check"); }
    if (afterMove->isCheck(color)) { throw IllegalMoveException("You can't move into check"); }

    return afterMove;
}


/*
* Method for getting a list of pseudo legal moves
* input: color of pieces
* output: vector of pairs that each contain the piece bitboard
* and the corresponding attack pattern bitboard
*/
std::vector<Move> BitBoard::getPseudoLegalMoves(bool color) const
{
    u64 currOccupancy = color ? this->m_whiteOccupancy : this->m_blackOccupancy;
    std::vector<Move> moves;
    for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
    {
        u64 board = this->m_pieces[color][piece];
        while (board)
        {
            int square = getLsbIndex(board);
            u64 pattern = this->m_attackPatterns[color][piece][square];
            switch (piece)
            {
                case pawn:
                    pattern = this->removePawnIllegalAtk(pattern, color) |
                        this->getPawnMovementPattern(square, color) |
                        this->getEnPassantPattern(square, color);
                    break;
                case rook:
                    pattern = this->removeRookBlockedAtk(square, pattern, color);
                    break;
                case bishop:
                    pattern = this->removeBishopBlockedAtk(square, pattern, color);
                    break;
                case queen:
                    pattern = this->removeQueenBlockedAtk(square, pattern, color);
                    break;
                case knight: case king:
                    pattern ^= pattern & currOccupancy;
                    break;
            }
            while (pattern)
            {
                int index = getLsbIndex(pattern);
                if ((1ULL << square) & this->m_pieces[color][pawn] && 
                    (1ULL << index) & getPromotionMask(color) && index != -1)
                {
                    moves.push_back({ (1ULL << square), (1ULL << index), queen, false, false });
                    moves.push_back({ (1ULL << square), (1ULL << index), rook, false, false });
                    moves.push_back({ (1ULL << square), (1ULL << index), bishop, false, false });
                    moves.push_back({ (1ULL << square), (1ULL << index), knight, false, false });
                }
                else if (index != -1) {
                    moves.push_back({ (1ULL << square), (1ULL << index), NO_PROMOTION, false, false });
                }
                pattern &= pattern - 1;
            }
            board &= board - 1;
        }
    }
    if (isCastlingPossible(false))
    {
        moves.push_back({ 0, 0, NO_PROMOTION, true, false });
    }
    if (isCastlingPossible(true))
    {
        moves.push_back({ 0, 0, NO_PROMOTION, true, true });
    }

    return moves;
}


/*
* Checks if move is found in the pseudo legal move list
* input: start and end square of move (int,int)
* output: true if move is found, false otherwise (bool)
*/
bool BitBoard::isMovePseudoLegal(int startSquare, int endSquare, bool color) const
{
    int piece = getPieceType(startSquare, color);
    u64 startPos = 0ULL;
    u64 endPos = 0ULL;
    auto moveList = color ? this->m_whiteMoveList : this->m_blackMoveList;

    SET_BIT(startPos, startSquare);
    SET_BIT(endPos, endSquare);

    for(auto it = moveList.begin(); it != moveList.end(); it++)
    {
        if (it->from == startPos && it->to == endPos)
        {
            return true;
        }
    }
    return false;
}


/*
* Method that parses a fen string and uses it to set the board state
* input: chess fen string
* output: None
*/
void BitBoard::parseFen(std::string fen)
{
    std::vector <std::string> fenParts = Parser::splitBySpace(fen);
    std::unordered_map<char, int> charToPiece = {
        {'p', pawn}, {'n',  knight},
        {'b',  bishop}, {'r',  rook},
        {'q',  queen}, {'k',  king}
    };
    std::unordered_map<char, int> charToCastle = {
        {'K', 2},
        {'Q', 4},
        {'k', 8},
        {'q', 16}
    };

    for (int i = 0, square = 0; i < fenParts[0].length(); i++)
    {
        if (fenParts[0][i] == '/')
        {
            square += square % 8;
            continue;
        }
        if (std::isdigit(fenParts[0][i]))
        {
            square += (int)fenParts[0][i] - 48;
            continue;
        }

        // Setting piece on board
        SET_BIT(this->m_pieces[fenParts[0][i] < 97 ? WHITE : BLACK]
            [charToPiece[fenParts[0][i] < 97 ? fenParts[0][i] + 32 : fenParts[0][i]]], square);
        square += 1;
    }

    this->m_moveFlags |= fenParts[1] == "w" ? 0b1 : 0b0; // Who's starting
    for (int i = 0; i < fenParts[2].length(); i++)
    {
        this->m_moveFlags |= charToCastle[fenParts[2][i]];
    }

    if (fenParts[3] != "-")
    {
        // Getting the en passant square from the char of the rank and file
        this->m_enPassantSquare = (fenParts[3][0] - 97) + (8 - (fenParts[3][1] - '0')) * 8;
    }
    else
    {
        this->m_enPassantSquare = NO_ENPASSANT;
    }
}


/*
* Method for initializing the values in an attack dictionary
* input: None
* output: None
*/
void BitBoard::initAtkDictionary()
{
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


/*
* Manipulates bitboards to play move
* input: board, color of current turn, piece, target, start Square, end Square, piece promotion
* output: None
*/
void BitBoard::expressMove(u64 nextPos[SIDES][NUMBER_OF_PIECES], bool color, int piece, int target, int startSquare, int endSquare, int promotionPiece) const
{
    SET_BIT(nextPos[color][promotionPiece == NO_PROMOTION ? piece : promotionPiece], endSquare);
    POP_BIT(nextPos[color][piece], startSquare);
    if (target != NO_CAPTURE)
    {
        // removing captured piece
        POP_BIT(nextPos[!color][target], endSquare);
    }
}


/*
* Method more making a castle move
* input: is Long castle (bool)
* output: bitboard of the next position
*/
std::shared_ptr<BitBoard> BitBoard::castleMove(bool isLongCastle) const
{
    u64 nextPosition[SIDES][NUMBER_OF_PIECES] = { 0ULL };
    uint8_t nextFlags = this->m_moveFlags;
    uint8_t nextEnPasssant = NO_ENPASSANT;
    bool color = COLOR;

    this->getPiecesCopy(nextPosition);
    u64 rookSquare = 0ULL; 
    rookSquare = (isLongCastle ? 1ULL : 128ULL) << (WHITE_ROOKS_OFFSET * color);

    if (!isCastlingPossible(isLongCastle))
    {  throw IllegalMoveException();}

    // making castle move on bitboard
    nextPosition[color][king] = isLongCastle ?
        nextPosition[color][king] >> 2 : nextPosition[color][king] << 2;
    nextPosition[color][rook] = isLongCastle ?
        nextPosition[color][rook] << 3 : nextPosition[color][rook] >> 2;
    nextPosition[color][rook] &= NO_SECOND_SEVENTH_RANK_MASK;
    nextPosition[color][rook] |= rookSquare ^ this->m_pieces[color][rook];

    nextFlags &= color ? 0b1111001 : 0b1100111;
    return createNextPosition(nextPosition, nextFlags, nextEnPasssant);
}


/*
* Method for finding which piece is on the given square
* input: square a piece is on
* output: piece identifier value (int)
*/
int BitBoard::getPieceType(int square, bool color) const
{
    u64 board = 0ULL;
    SET_BIT(board, square);

    for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
    {
        if (board & this->m_pieces[color][piece])
        {
            return piece;
        }
    }
    return -1;
}

int BitBoard::getPieceType(u64 square, bool color) const
{
    for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
    {
        if (square & this->m_pieces[color][piece])
        {
            return piece;
        }
    }
    return -1;
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
    return bitCount((board & -board) - 1);
}


/*
* Method for checking if the king is in check
* input: color of king to check
* output: true if the king is in check, false otherwise.
*/
bool BitBoard::isCheck(bool color) const
{
    return this->m_pieces[color][king] & (!color ? this->m_whiteAtkedSqrs : this->m_blackAtkedSqrs);
}

/*
* Checks if there is Checkmate for a given color on the board
* input: color of piece to check on
* output: True=Checkmate, False=No Checkmate
*/
bool BitBoard::isMate(bool color) const
{
    if (!this->isCheck(color))
    {
        return false;
    }
    auto moves = color ? this->m_whiteMoveList : this->m_blackMoveList;
    for (int i = 0; i < moves.size(); i++)
    {
        try 
        {
            Move option = moves[i];
            if (option.castle)
            {
                this->castleMove(option.isLong);
            }
            else
            {
                this->move(getLsbIndex(option.from), getLsbIndex(option.to), option.promotion);
            }
            return false;
        }
        catch (...)
        {
            continue;
        }
    }
    return true;
}


/*
* Checks if there is Stalemate for a given color on the board
* input: color of piece to check on
* output: True=Stalemate, False=No Stalemate
*/
bool BitBoard::isStale(bool color) const
{
    if (this->isCheck(color) || color != (COLOR))
    {
        return false;
    }
    auto moves = color ? this->m_whiteMoveList : this->m_blackMoveList;
    for (int i = 0; i < moves.size(); i++)
    {
        try
        {
            Move option = moves[i];
            if (option.castle)
            {
                this->castleMove(option.isLong);
            }
            else
            {
                this->move(getLsbIndex(option.from), getLsbIndex(option.to), option.promotion);
            }
            return false;
        }
        catch (std::exception& e)
        {
            continue;
        }
    }
    return true;
}


/*
* Method to get the  occupancy board with the location of all pieces of a specific color
* input: color of pieces
* output: a occupancy bitboard that contains all pieces of given color (u64)
*/
u64 BitBoard::getSideOccupancy(const bool color) const
{
    u64 unifiedBoard = 0ULL;
    for (int i = 0; i < NUMBER_OF_PIECES; i++)
    {
        unifiedBoard |= this->m_pieces[color][i];
    }
    return unifiedBoard;
}


/*
* Method for getting all the attacked squares of a given side on the board
* input: side (white|black) (bool)
* output: bitboard of all attacked squares (u64)
*/
u64 BitBoard::getAttackSqrs(const bool color) const
{
    u64 attack = 0ULL;
    std::vector<Move> pseudoLegal = color ?
        this->m_whiteMoveList :
        this->m_blackMoveList;
    for (auto it = pseudoLegal.begin(); it != pseudoLegal.end(); it++)
    {
        attack |= it->to;
    }
    return attack;
}


/*
* Method that gives the appropriate promotion mask depending on the current
* color turn
* input: None
* output: Promotion rank mask (u64)
*/
u64 BitBoard::getPromotionMask(bool color) const
{
    return color ? 255ULL : 18374686479671623680ULL;
}


/*
* Method for removing blocked attack squares from a bishop attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeBishopBlockedAtk(int square, u64 atk, bool color) const
{
    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;
    bool isBlocked = false;
    u64 currColorOccupancy = color ? this->m_whiteOccupancy : this->m_blackOccupancy;
    u64 oppositeColorOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;

    // bishop moving shl 9
    for (r = rank + 1, f = file + 1, isBlocked = false; r <= 7 && f <= 7; r++, f++)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & oppositeColorOccupancy;
    }

    // bishop moving shr 9
    for (r = rank + -1, f = file - 1, isBlocked = false; r >= 0 && f >= 0; r--, f--)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & oppositeColorOccupancy;
    }

    // bishop moving shr 7
    for (r = rank - 1, f = file + 1, isBlocked = false; r >= 0 && f <= 7; r--, f++)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & oppositeColorOccupancy;
    }

    // bishop moving shl 7
    for (r = rank + 1, f = file - 1, isBlocked = false; r <= 7 && f >= 0; r++, f--)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + f)) & oppositeColorOccupancy;
    }

    return atk;
}


/*
* Method for removing blocked attack squares from a rook attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeRookBlockedAtk(int square, u64 atk, bool color) const
{
    int f = 0, r = 0;
    int rank = square / 8;
    int file = square % 8;
    bool isBlocked = false;
    u64 currColorOccupancy = color ? this->m_whiteOccupancy : this->m_blackOccupancy;
    u64 oppositeColorOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;

    // rook shl 8
    for (r = rank + 1, isBlocked = false; r <= 7; r++)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + file)) & currColorOccupancy); }
        if(isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + file));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + file)) & oppositeColorOccupancy;
    }

    // rook shr 8
    for (r = rank - 1, isBlocked = false; r >= 0; r--)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((r * 8) + file)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((r * 8) + file));
            continue;
        }
        isBlocked = (1ULL << ((r * 8) + file)) & oppositeColorOccupancy;
    }

    // rook shl 1
    for (f = file + 1, isBlocked = false; f <= 7; f++)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((rank * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((rank * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((rank * 8) + f)) & oppositeColorOccupancy;
    }

    // rook shr 1
    for (f = file - 1, isBlocked = false; f >= 0; f--)
    {
        if (!isBlocked) { isBlocked = ((1ULL << ((rank * 8) + f)) & currColorOccupancy); }
        if (isBlocked)
        {
            atk ^= (1ULL << ((rank * 8) + f));
            continue;
        }
        isBlocked = (1ULL << ((rank * 8) + f)) & oppositeColorOccupancy;
    }

    return atk;
}


/*
* Method for removing blocked attack squares from a queen attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeQueenBlockedAtk(int square, u64 atk, bool color) const
{
    u64 diagonal = atk & this->m_attackPatterns[WHITE][bishop][square];
    u64 lateral = atk & this->m_attackPatterns[WHITE][rook][square];
    return this->removeBishopBlockedAtk(square, diagonal, color) | this->removeRookBlockedAtk(square, lateral, color);
}


/*
* Method that removes attack squares from a pawn attack pattern
* that are not occupied by an enemy piece
* input: pawn attack pattern
* output: updated attack pattern
*/
u64 BitBoard::removePawnIllegalAtk(u64 atk, bool color) const
{
    u64 oppositeOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;
    return atk & oppositeOccupancy;
}


/*
* Method for getting the movement pattern of a pawn based on the color 
* and square the pawn is on
* input: square the pawn is on
* output: movement pattern seperate to the attack pattern (u64)
*/
u64 BitBoard::getPawnMovementPattern(int square, bool color) const
{
    constexpr u64 doubleJumpMask = 71776119061282560ULL;
    u64 ptrn = 0ULL;
    u64 movement = 0ULL;
    SET_BIT(ptrn, square);
    bool isDoubleJump = ptrn & doubleJumpMask;
    u64 occupancy = this->m_whiteOccupancy | this->m_blackOccupancy;

    if (!((color ? ptrn >> 8 : ptrn << 8) & occupancy))
    {   movement |= color ? ptrn >> 8 : ptrn << 8; }
    if (!(movement & occupancy) && isDoubleJump)
    {   movement |= color ? movement >> 8 : movement << 8; }

    return movement;
}


/*
* Method for getting an en passant attack bitboard based on the location of the pawn
* input: Square the attacking pawn is on
* output: bitboard attack pattern
*/
u64 BitBoard::getEnPassantPattern(int square, bool color) const
{
    u64 board = 0ULL;
    u64 enPassantBoard = 0ULL;
    SET_BIT(board, square);
    if (this->m_enPassantSquare == NO_ENPASSANT)
    {
        return enPassantBoard;
    }
    SET_BIT(enPassantBoard, this->m_enPassantSquare);
    if (color)
    {
        if (((board >> 9) | (board >> 7)) & enPassantBoard)
        {
            return enPassantBoard;
        }
    }
    else if(!color)
    {
        if (((board << 9) | (board << 7)) & enPassantBoard)
        {
            return enPassantBoard;
        }
    }
    return 0ULL;
}


/*
* Method for copying the current state of the board
* input: array of bitboards to copy into
* output: None
*/
void BitBoard::getPiecesCopy(u64 pieces[SIDES][NUMBER_OF_PIECES]) const
{
    for (int i = 0; i < SIDES; i++)
    {
        for (int j = 0; j < NUMBER_OF_PIECES; j++)
        {
            pieces[i][j] = this->m_pieces[i][j];
        }
    }
}

uint8_t BitBoard::getFlags() const
{
    return this->m_moveFlags;
}

uint8_t BitBoard::getEnPassant() const
{
    return this->m_enPassantSquare;
}

/*
* Method for checking if castling is possible
* input: castle type to check (short/long) (bool)
* output: true=castling allowed, false castling is not allowed
*/
bool BitBoard::isCastlingPossible(bool isLongCastle) const
{
    u64 fullOccupancy = this->m_whiteOccupancy | this->m_blackOccupancy;
    bool color = this->m_moveFlags & 0b1;

    // mask for empty squares between king and rook
    u64 emptyMask = (isLongCastle ? 14ULL : 96ULL) << (56 * color);
    u64 rookSquare = (isLongCastle ? 1ULL : 128ULL) << (56 * color);
    u64 kingSquare = 16ULL << (56 * color);


    if ((this->m_moveFlags & (0b1 << (1 + (!color * 2) + isLongCastle))) == 0)
    {   return false; }
    if (emptyMask & fullOccupancy)
    {   return false; }
    if (!(kingSquare & this->m_pieces[color][king]) || !(rookSquare & this->m_pieces[color][rook]))
    {   return false; }

    return true;
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
