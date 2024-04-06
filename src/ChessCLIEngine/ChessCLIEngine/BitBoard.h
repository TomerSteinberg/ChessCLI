#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <deque>
#include <random>

#include <assert.h>     /* assert */


#include "MissingPieceException.h"
#include "IllegalMoveException.h"

#define NO_CAPTURE -1
#define NO_PROMOTION -1
#define NUMBER_OF_PIECES 6
#define NUMBER_OF_SQUARES 64
#define ZOBRIST_SQUARES 146
#define BLACK 0
#define WHITE 1
#define SIDES 2
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8
#define NO_ENPASSANT 255
#define LEFT_CORNERS 72057594037927937ULL
#define TOP_CORNERS 129ULL
#define BOTTOM_CORNERS 9295429630892703744ULL
#define PAWN_DOUBLE_JUMP_DIFFERENCE 16
#define LOWER_CASE_ASCII_DIFFERENCE 32
#define WHITE_ROOKS_OFFSET 56
#define COLOR (this->m_moveFlags & WHITE)

#define GET_BIT(board, square) ((board & (1ULL << square)) ? 1 : 0)
#define SET_BIT(board, square) (board |= (1ULL << square))
#define POP_BIT(board, square) (GET_BIT(board, square) ? board ^= (1ULL << square) : 0)

typedef unsigned long long u64;

// 3d array of shared pointers in shape of attack dictionary
typedef std::shared_ptr<std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>[SIDES]> AttackDictionary;
typedef std::shared_ptr<std::shared_ptr<u64[512]>[NUMBER_OF_SQUARES]> BishopAttack;
typedef std::shared_ptr<std::shared_ptr<u64[4096]>[NUMBER_OF_SQUARES]> RookAttack;


enum Squares{
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
};


enum Pieces {
	pawn, knight, bishop, rook, queen, king
};

struct Move {
	u64 from;
	u64 to;
	int promotion;
	bool castle;
	bool isLong;
};


class BitBoard
{
public:
	BitBoard(std::string fen);
	explicit BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], const AttackDictionary& attackPatterns, uint8_t flags, uint8_t enPassant,
		const BishopAttack& bishopAttacks, const RookAttack& rookAttacks);

	int evaluate() const;

	std::shared_ptr<BitBoard> move(const int startSquare, int endSquare, const int promotionPiece=NO_PROMOTION) const;
	std::shared_ptr<BitBoard> castleMove(const bool isLong) const;
	std::string getFen() const;
	u64 getZobristHash() const;
	std::deque<Move> getMoveList();

	inline bool isCheck(bool color) const;
	bool isMate(bool color) const;
	bool isStale(bool color) const;

	void printBoard(bool isUnicode=false) const;
	static inline int8_t getLsbIndex(u64 board);
	inline void getPiecesCopy(u64 pieces[SIDES][NUMBER_OF_PIECES]) const;
	uint8_t getFlags() const;
	uint8_t getEnPassant() const;

private:
	friend class MoveSearch;
	std::pair<int8_t, int8_t> makeMoveNoCopy(Move make);
	void unmakeMoveNoCopy(Move unmake, int8_t capturedSquare, int8_t capturedPiece, u64 whiteAtkedSqrs,
		u64 blackAtkedSqrs, u64 hash, u64 whiteOcc, u64 blackOcc, std::deque<Move> moveList,
		uint8_t enPassantSquare, uint8_t flags);

	/* Move flags:
	* LSB - Side flag
	* White castle
	* White long castle
	* Black castle
	* MSB - Black long castle
	*/
	uint8_t m_moveFlags;
	uint8_t m_enPassantSquare;
	const AttackDictionary m_attackPatterns;
	const BishopAttack m_bishopAttacks;
	const RookAttack m_rookAttacks;
	u64 m_pieces[SIDES][NUMBER_OF_PIECES];
	std::deque<Move> m_moveList;
	u64 m_whiteAtkedSqrs;
	u64 m_blackAtkedSqrs;
	u64 m_whiteOccupancy;
	u64 m_blackOccupancy;
	u64 m_hash;
	static const u64 bishopMagic[NUMBER_OF_SQUARES];
	static const u64 rookMagic[NUMBER_OF_SQUARES];
	static const int bishopRelevantBits[64];
	static const int rookRelevantBits[64];
	static u64 zobristKeys[SIDES][NUMBER_OF_PIECES][ZOBRIST_SQUARES];

	inline std::shared_ptr<BitBoard> createNextPosition(u64 nextPos[SIDES][NUMBER_OF_PIECES], uint8_t nextFlags, uint8_t nextEnPassant) const;
	inline std::deque<Move> getLegalMoves(const bool color);
	inline bool isMoveLegal(int from, int to, u64 fromBB, u64 toBB, bool color);
	inline bool isMoveInMoveList(int startSquare, int endSquare, bool color) const;
	bool dynamicCheck(bool color);

	void parseFen(std::string fen);
	inline u64 getInitialZobristHash() const;
	void initAtkDictionary();
	void initZobristKeys();
	void initSliderAttacks(bool isBishop);
	inline void expressMove(u64 nextPos[SIDES][NUMBER_OF_PIECES], bool color, int piece, int target, int startSquare, int endSquare, int promotionPiece) const;

	int getPieceType(int square, bool color) const;
	int getPieceType(u64 square, bool color) const;
	static inline int bitCount(u64 board);
	int getProximityCount(int square, bool color) const;
	inline u64 getSideOccupancy(const bool color) const; 
	inline u64 getAttackSqrs(const bool color) const;
	constexpr inline u64 getPromotionMask(bool color) const;
	u64 setOccupancy(int index, int maskBitCount, u64 attackMask)const ;


	inline u64 getBishopAtk(int square, u64 occupancy) const;
	inline u64 getRookAtk(int square, u64 occupancy) const;
	u64 removeBishopBlockedAtk(int square, u64 occupancy) const;
	u64 removeRookBlockedAtk(int square, u64 occupancy) const;
	inline u64 removeQueenBlockedAtk(int square, u64 occupancy) const;
	u64 removePawnIllegalAtk(u64 atk, bool color) const;
	u64 getPawnMovementPattern(int square, bool color) const;
	u64 getEnPassantPattern(int square, bool color) const;
	
	bool isCastlingPossible(bool isLongCastle) const;

	//====== Attack Patterns ======//
	static u64 calcWhitePawnAtkPattern(int square);
	static u64 calcBlackPawnAtkPattern(int square);
	static u64 calcKnightAtkPattern(int square);
	static u64 calcRookAtkPattern(int square);
	static u64 calcBishopAtkPattern(int square);
	static u64 calcKingAtkPattern(int square);
	static u64 calcQueenAtkPattern(int square);


	//======= Positional Evaluation =======//
	int evaluatePawns(bool color) const;
};

#endif

