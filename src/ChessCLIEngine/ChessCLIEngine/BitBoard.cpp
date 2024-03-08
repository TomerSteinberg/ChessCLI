#include "BitBoard.h"
#include "Parser.h"
#include <Windows.h>


u64 BitBoard::zobristKeys[SIDES][NUMBER_OF_PIECES][ZOBRIST_SQUARES] = { 0 };

const u64 BitBoard::rookMagic[64] = {
    0x8a80104000800020ULL,
    0x140002000100040ULL,
    0x2801880a0017001ULL,
    0x100081001000420ULL,
    0x200020010080420ULL,
    0x3001c0002010008ULL,
    0x8480008002000100ULL,
    0x2080088004402900ULL,
    0x800098204000ULL,
    0x2024401000200040ULL,
    0x100802000801000ULL,
    0x120800800801000ULL,
    0x208808088000400ULL,
    0x2802200800400ULL,
    0x2200800100020080ULL,
    0x801000060821100ULL,
    0x80044006422000ULL,
    0x100808020004000ULL,
    0x12108a0010204200ULL,
    0x140848010000802ULL,
    0x481828014002800ULL,
    0x8094004002004100ULL,
    0x4010040010010802ULL,
    0x20008806104ULL,
    0x100400080208000ULL,
    0x2040002120081000ULL,
    0x21200680100081ULL,
    0x20100080080080ULL,
    0x2000a00200410ULL,
    0x20080800400ULL,
    0x80088400100102ULL,
    0x80004600042881ULL,
    0x4040008040800020ULL,
    0x440003000200801ULL,
    0x4200011004500ULL,
    0x188020010100100ULL,
    0x14800401802800ULL,
    0x2080040080800200ULL,
    0x124080204001001ULL,
    0x200046502000484ULL,
    0x480400080088020ULL,
    0x1000422010034000ULL,
    0x30200100110040ULL,
    0x100021010009ULL,
    0x2002080100110004ULL,
    0x202008004008002ULL,
    0x20020004010100ULL,
    0x2048440040820001ULL,
    0x101002200408200ULL,
    0x40802000401080ULL,
    0x4008142004410100ULL,
    0x2060820c0120200ULL,
    0x1001004080100ULL,
    0x20c020080040080ULL,
    0x2935610830022400ULL,
    0x44440041009200ULL,
    0x280001040802101ULL,
    0x2100190040002085ULL,
    0x80c0084100102001ULL,
    0x4024081001000421ULL,
    0x20030a0244872ULL,
    0x12001008414402ULL,
    0x2006104900a0804ULL,
    0x1004081002402ULL,
};


const u64 BitBoard::bishopMagic[64] = {
    0x40040844404084ULL,
    0x2004208a004208ULL,
    0x10190041080202ULL,
    0x108060845042010ULL,
    0x581104180800210ULL,
    0x2112080446200010ULL,
    0x1080820820060210ULL,
    0x3c0808410220200ULL,
    0x4050404440404ULL,
    0x21001420088ULL,
    0x24d0080801082102ULL,
    0x1020a0a020400ULL,
    0x40308200402ULL,
    0x4011002100800ULL,
    0x401484104104005ULL,
    0x801010402020200ULL,
    0x400210c3880100ULL,
    0x404022024108200ULL,
    0x810018200204102ULL,
    0x4002801a02003ULL,
    0x85040820080400ULL,
    0x810102c808880400ULL,
    0xe900410884800ULL,
    0x8002020480840102ULL,
    0x220200865090201ULL,
    0x2010100a02021202ULL,
    0x152048408022401ULL,
    0x20080002081110ULL,
    0x4001001021004000ULL,
    0x800040400a011002ULL,
    0xe4004081011002ULL,
    0x1c004001012080ULL,
    0x8004200962a00220ULL,
    0x8422100208500202ULL,
    0x2000402200300c08ULL,
    0x8646020080080080ULL,
    0x80020a0200100808ULL,
    0x2010004880111000ULL,
    0x623000a080011400ULL,
    0x42008c0340209202ULL,
    0x209188240001000ULL,
    0x400408a884001800ULL,
    0x110400a6080400ULL,
    0x1840060a44020800ULL,
    0x90080104000041ULL,
    0x201011000808101ULL,
    0x1a2208080504f080ULL,
    0x8012020600211212ULL,
    0x500861011240000ULL,
    0x180806108200800ULL,
    0x4000020e01040044ULL,
    0x300000261044000aULL,
    0x802241102020002ULL,
    0x20906061210001ULL,
    0x5a84841004010310ULL,
    0x4010801011c04ULL,
    0xa010109502200ULL,
    0x4a02012000ULL,
    0x500201010098b028ULL,
    0x8040002811040900ULL,
    0x28000010020204ULL,
    0x6000020202d0240ULL,
    0x8918844842082200ULL,
    0x4010011029020020ULL,
};


const int BitBoard::rookRelevantBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};


const int BitBoard::bishopRelevantBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};


BitBoard::BitBoard(std::string fen) : m_attackPatterns(AttackDictionary(new std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>[SIDES])),
    m_bishopAttacks(BishopAttack(new std::shared_ptr<u64[512]>[NUMBER_OF_SQUARES])),
    m_rookAttacks(RookAttack(new std::shared_ptr<u64[4096]>[NUMBER_OF_SQUARES]))
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
    for (int square = 0; square < NUMBER_OF_SQUARES; square++)
    {
        this->m_bishopAttacks[square] = std::shared_ptr<u64[512]>(new u64[512]);
        this->m_rookAttacks[square] = std::shared_ptr<u64[4096]>(new u64[4096]);
    }
    initZobristKeys();
    parseFen(fen);
    initAtkDictionary();
    initSliderAttacks(true);
    initSliderAttacks(false);

    this->m_whiteOccupancy = getSideOccupancy(WHITE);
    this->m_blackOccupancy = getSideOccupancy(BLACK);
    this->m_whiteMoveList = getPseudoLegalMoves(WHITE);
    this->m_blackMoveList = getPseudoLegalMoves(BLACK);
    this->m_whiteAtkedSqrs = getAttackSqrs(WHITE);
    this->m_blackAtkedSqrs = getAttackSqrs(BLACK);
    this->m_hash = getInitialZobristHash();
}


// Using shallow copy for attack dictionary to avoid unnecessary computation 
BitBoard::BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], const AttackDictionary& attackPatterns, uint8_t flags, uint8_t enPassant,
    const BishopAttack& bishopAttacks, const RookAttack& rookAttacks) :
    m_attackPatterns(attackPatterns), m_enPassantSquare(enPassant) ,m_moveFlags(flags),
    m_bishopAttacks(bishopAttacks), m_rookAttacks(rookAttacks)
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
    this->m_hash = this->getInitialZobristHash();
}


/*
* Evaluates the current position
* input: None
* output: Evaluation number (double)
*/
int BitBoard::evaluate() const
{
    const int PIECE_VALUES[] = { 100, 300, 300, 500, 900 };
    int evaluation = 0;
    bool color = COLOR;

    int whiteProximityCount = getProximityCount(getLsbIndex(this->m_pieces[WHITE][king]), WHITE) * 10;
    int blackProximityCount = getProximityCount(getLsbIndex(this->m_pieces[BLACK][king]), BLACK) * 10;

    for (int i = 0; i < NUMBER_OF_PIECES - 1; i++)
    {
        evaluation += (bitCount(this->m_pieces[WHITE][i]) * PIECE_VALUES[i]) 
                      - (bitCount(this->m_pieces[BLACK][i]) * PIECE_VALUES[i]);
    }
    if (this->isCheck(!color))
    {
        evaluation += 70;
    }
    evaluation += this->m_whiteMoveList.size() - this->m_blackMoveList.size();

    evaluation += blackProximityCount - whiteProximityCount;
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

    const bool color = COLOR;
    bool isAttackingEnPassant = false;
    int target = NO_CAPTURE;
    int piece = 0;
    u64 startPos = 0ULL, endPos = 0ULL;
    u64 nextPosition[SIDES][NUMBER_OF_PIECES] = { 0ULL };
    const u64 promotionMask = this->getPromotionMask(color);
    uint8_t nextFlags = this->m_moveFlags, nextEnPasssant = NO_ENPASSANT;


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


u64 BitBoard::getZobristHash() const
{
    return this->m_hash;
}


std::deque<Move> BitBoard::getMoveList()
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
    std::shared_ptr<BitBoard> afterMove = std::make_shared<BitBoard>(nextPos, this->m_attackPatterns, nextFlags, nextEnPassant, this->m_bishopAttacks, this->m_rookAttacks);

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
std::deque<Move> BitBoard::getPseudoLegalMoves(bool color) const
{
    u64 currOccupancy = color ? this->m_whiteOccupancy : this->m_blackOccupancy;
    u64 oppositeOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;
    u64 oppositeAtk = color ? this->m_blackAtkedSqrs : this->m_whiteAtkedSqrs;
    std::deque<Move> moves;
    int mostImportantIndex = 0;
    int leastImportantIndex = 0;
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
                    pattern = removeRookBlockedAtk(square, currOccupancy | oppositeOccupancy) & (~currOccupancy);
                    break;
                case bishop:
                    pattern = removeBishopBlockedAtk(square, currOccupancy | oppositeOccupancy) & (~currOccupancy);
                    break;
                case queen:
                    pattern = this->removeQueenBlockedAtk(square) & (~currOccupancy);
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

                    if (getPieceType(index, !color) > getPieceType(square, color))
                    {
                        moves.push_front({ (1ULL << square), (1ULL << index), NO_PROMOTION, false, false });
                        mostImportantIndex++;
                    }
                    else if (getPieceType(index, !color) != NO_CAPTURE)
                    {
                        moves.insert(moves.begin() + mostImportantIndex , { (1ULL << square), (1ULL << index), NO_PROMOTION, false, false });
                    }
                    else if (index & oppositeAtk)
                    {
                        moves.push_back({ (1ULL << square), (1ULL << index), NO_PROMOTION, false, false });
                        leastImportantIndex++;
                    }
                    else
                    {
                        moves.insert(moves.end() - leastImportantIndex, { (1ULL << square), (1ULL << index), NO_PROMOTION, false, false });
                    }
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

    for (size_t i = 0, square = 0; i < fenParts[0].length(); i++)
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
    for (size_t i = 0; i < fenParts[2].length(); i++)
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
* Calculates the initial Zobrist Hash of position
* input: None
* output: Zobrist Hash
*/
u64 BitBoard::getInitialZobristHash() const
{
    u64 hash = 0ULL;
    uint8_t flags = this->m_moveFlags;
    flags >>= 1;

    for (int color = 0; color < SIDES; color++)
    {
        for (int i = 0; i < NUMBER_OF_PIECES; i++)
        {
            u64 piece = this->m_pieces[color][i];
            while (piece)
            {
                hash ^= this->zobristKeys[color][i][getLsbIndex(piece)];
                piece &= piece - 1;
            }
        }
    }
    if (this->m_enPassantSquare != NO_ENPASSANT)
    {
        hash ^= BitBoard::zobristKeys[COLOR][pawn][this->m_enPassantSquare * 2];
    }
    hash ^= BitBoard::zobristKeys[WHITE][pawn][(COLOR)+129];
    hash ^= BitBoard::zobristKeys[WHITE][pawn][131 + flags];

    return hash;
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
* Initialize Zorbist Key array
* input: None
* output: None
*/
void BitBoard::initZobristKeys()
{
    std::random_device randomDevice;
    std::mt19937_64 rng(randomDevice());
    std::uniform_int_distribution<u64> dist(std::llround(std::pow(2, 61)), std::llround(std::pow(2, 62)));
    for (int side = 0; side < SIDES; side++)
    {
        for (int piece = 0; piece < NUMBER_OF_PIECES; piece++)
        {
            for(int square = 0; square < ZOBRIST_SQUARES; square++)
            {
                BitBoard::zobristKeys[side][piece][square] = dist(rng);
            }
        }
    }
}


/*
* Inits slider attack magic bitboards
* input: is Bishop piece (false means rook)
* output: None
*/
void BitBoard::initSliderAttacks(bool isBishop)
{
    for (int square = 0; square < NUMBER_OF_SQUARES; square++)
    {
        u64 bishopAtk = this->m_attackPatterns[WHITE][bishop][square];
        u64 rookAtk = this->m_attackPatterns[WHITE][rook][square];

        u64 mask = isBishop ? bishopAtk : rookAtk;
        int bits = bitCount(mask);

        int occupancyVariations = 1 << bits;

        for (int count = 0; count < occupancyVariations; count++)
        {
            if (isBishop)
            {
                u64 occupancy = setOccupancy(count, bits, mask);
                u64 magicIndex = occupancy * bishopMagic[square] >> 64 - bishopRelevantBits[square];
                this->m_bishopAttacks[square][magicIndex] = removeBishopBlockedAtk(square, occupancy);
            }
            else
            {
                u64 occupancy = setOccupancy(count, bits, mask);
                u64 magicIndex = occupancy * rookMagic[square] >> 64 - rookRelevantBits[square];
                this->m_rookAttacks[square][magicIndex] = removeRookBlockedAtk(square, occupancy);
            }
        }
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


/*
* Gets a piece type on a square given a color
* input: square and color
* output: piece type (pieces enum)
*/
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
unsigned long BitBoard::getLsbIndex(u64 board)
{
    static const int lookup67[68] = {
   64,  0,  1, 39,  2, 15, 40, 23,
    3, 12, 16, 59, 41, 19, 24, 54,
    4, -1, 13, 10, 17, 62, 60, 28,
   42, 30, 20, 51, 25, 44, 55, 47,
    5, 32, -1, 38, 14, 22, 11, 58,
   18, 53, 63,  9, 61, 27, 29, 50,
   43, 46, 31, 37, 21, 57, 52,  8,
   26, 49, 45, 36, 56,  7, 48, 35,
    6, 34, 33, -1 };
    return lookup67[(board & -(long long)board) % 67];
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
    for (size_t i = 0; i < moves.size(); i++)
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
    for (size_t i = 0; i < moves.size(); i++)
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
    u64 oppositeOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;
    std::deque<Move> pseudoLegal = color ?
        this->m_whiteMoveList :
        this->m_blackMoveList;
    for (auto it = pseudoLegal.begin(); it != pseudoLegal.end(); it++)
    {
        if(getPieceType(it->from, color) == pawn && !(it->to & oppositeOccupancy))
        {
            continue;
        }
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
* Sets the occupancy based on an attack mask an index and a bitcount of mask
* input: index, mask bit count and mask board
* output: occupancy
*/
u64 BitBoard::setOccupancy(int index, int maskBitCount, u64 attackMask)
{
    u64 occupancy = 0ULL;

    for (int count = 0; count < maskBitCount; count++)
    {
        int square = getLsbIndex(attackMask);
        POP_BIT(attackMask, square);
        if (index & (1 << count))
            occupancy |= (1ULL << square);
    }
    return occupancy;
}


/*
* Gets a bishop attack from the magic bitboard
* input: square and occupancy of board
* output: pre caluclated bishop attack
*/
u64 BitBoard::getBishopAtk(int square, u64 occupancy) const
{
    occupancy &= this->m_attackPatterns[WHITE][bishop][square];
    occupancy *= bishopMagic[square];
    occupancy >>= 64 - bishopRelevantBits[square];
    return m_bishopAttacks[square][occupancy];
}


/*
* Gets a rook attack from the magic bitboard
* input: square and occupancy of board
* output: pre caluclated rook attack
*/
u64 BitBoard::getRookAtk(int square, u64 occupancy) const
{
    occupancy &= this->m_attackPatterns[WHITE][rook][square];
    occupancy *= rookMagic[square];
    occupancy >>= 64 - rookRelevantBits[square];
    return m_rookAttacks[square][occupancy];
}


/*
* Method for removing blocked attack squares from a bishop attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeBishopBlockedAtk(int square, u64 occupancy) const
{
    u64 attack = 0ULL;

    int f, r;
    int targetRank = square / 8;
    int targetFile = square % 8;

    // generate attacks
    for (r = targetRank + 1, f = targetFile + 1; r <= 7 && f <= 7; r++, f++)
    {
        attack |= (1ULL << (r * 8 + f));
        if (occupancy & (1ULL << (r * 8 + f))) { break; }
    }

    for (r = targetRank + 1, f = targetFile - 1; r <= 7 && f >= 0; r++, f--)
    {
        attack |= (1ULL << (r * 8 + f));
        if (occupancy & (1ULL << (r * 8 + f))) { break; }
    }

    for (r = targetRank - 1, f = targetFile + 1; r >= 0 && f <= 7; r--, f++)
    {
        attack |= (1ULL << (r * 8 + f));
        if (occupancy & (1ULL << (r * 8 + f))) { break; }
    }

    for (r = targetRank - 1, f = targetFile - 1; r >= 0 && f >= 0; r--, f--)
    {
        attack |= (1ULL << (r * 8 + f));
        if (occupancy & (1ULL << (r * 8 + f))) { break; }
    }
    return attack;
}


/*
* Method for removing blocked attack squares from a rook attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeRookBlockedAtk(int square, u64 occupancy) const
{
    u64 attack = 0ULL;

    int file, rank;

    int targetRank = square / 8;
    int targetFile = square % 8;

    for (rank = targetRank + 1; rank <= 7; rank++)
    {
        attack |= (1ULL << (rank * 8 + targetFile));
        if (occupancy & (1ULL << (rank * 8 + targetFile))) { break; }
    }

    for (rank = targetRank - 1; rank >= 0; rank--)
    {
        attack |= (1ULL << (rank * 8 + targetFile));
        if (occupancy & (1ULL << (rank * 8 + targetFile))) { break; }
    }

    for (file = targetFile + 1; file <= 7; file++)
    {
        attack |= (1ULL << (targetRank * 8 + file));
        if (occupancy & (1ULL << (targetRank * 8 + file))) { break; }
    }

    for (file = targetFile - 1; file >= 0; file--)
    {
        attack |= (1ULL << (targetRank * 8 + file));
        if (occupancy & (1ULL << (targetFile * 8 + file))) { break; }
    }

    return attack;
}


/*
* Method for removing blocked attack squares from a queen attack pattern
* input: piece square and attack pattern
* output: attack pattern without blocked squares
*/
u64 BitBoard::removeQueenBlockedAtk(int square) const
{
    u64 diagonal = removeBishopBlockedAtk(square, m_whiteOccupancy | m_blackOccupancy);
    u64 lateral = removeRookBlockedAtk(square, m_whiteOccupancy | m_blackOccupancy);
    return lateral | diagonal;
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
    if (!((color ? movement >> 8 : movement << 8) & occupancy) && isDoubleJump)
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
    constexpr uint64_t m1 = 0x5555555555555555; 
    constexpr uint64_t m2 = 0x3333333333333333; 
    constexpr uint64_t m4 = 0x0f0f0f0f0f0f0f0f; 
    constexpr uint64_t h01 = 0x0101010101010101;
    board -= (board >> 1) & m1;
    board = (board & m2) + ((board >> 2) & m2);
    board = (board + (board >> 4)) & m4;
    return (board * h01) >> 56;
}


/*
* Gets the proximity to the king of enemy pieces (based on 2 square distance radius)
* input: square of king, color of king
* output: number of enemy pieces in proximity
*/
int BitBoard::getProximityCount(int square, bool color) const
{
    u64 oppositeOccupancy = color ? this->m_blackOccupancy : this->m_whiteOccupancy;
    u64 nextLayer = 0ULL;
    u64 kingAttack = this->m_attackPatterns[color][king][square];
    while (kingAttack)
    {
        nextLayer |= this->m_attackPatterns[color][king][getLsbIndex(kingAttack)];
        kingAttack &= kingAttack - 1;
    }
    return bitCount(nextLayer & oppositeOccupancy);
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
    for(r = rank + 1, f = file + 1; r <= 6 && f <= 6; r++, f++)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shr 9
    for(r = rank + -1, f = file - 1; r >= 1 && f >= 1; r--, f--)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shr 7
    for(r = rank - 1, f = file + 1; r >= 1 && f <= 6; r--, f++)
    { attack |= (1ULL << ((r * 8) + f)); }

    // bishop moving shl 7
    for(r = rank + 1, f = file - 1; r <= 6 && f >= 1; r++, f--)
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
    for (r = rank + 1; r <= 6; r++)
    { attack |= (1ULL << ((r * 8) + file)); }

    // rook shr 8
    for (r = rank -1; r >= 1; r--)
    { attack |= (1ULL << ((r * 8) + file)); }

    // rook shl 1
    for (f = file + 1; f <= 6; f++)
    { attack |= (1ULL << ((rank * 8) + f)); }

    // rook shr 1
    for (f = file - 1;f >= 1; f--)
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


int BitBoard::evaluatePawns(bool color) const
{
    return 0;
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
