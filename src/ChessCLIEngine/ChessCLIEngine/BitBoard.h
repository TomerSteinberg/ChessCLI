#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>


#include "MissingPieceException.h"
#include "IllegalMoveException.h"

#define NO_CAPTURE -1
#define NO_PROMOTION -1
#define NUMBER_OF_PIECES 6
#define NUMBER_OF_SQUARES 64
#define BLACK 0
#define WHITE 1
#define SIDES 2
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8
#define NO_ENPASSANT 255
#define CORNERS 9295429630892703873ULL
#define LEFT_CORNERS 72057594037927937ULL
#define PAWN_DOUBLE_JUMP_DIFFERENCE 16
#define LOWER_CASE_ASCII_DIFFERENCE 32
#define COLOR this->m_moveFlags & WHITE

#define GET_BIT(board, square) ((board & (1ULL << square)) ? 1 : 0)
#define SET_BIT(board, square) (board |= (1ULL << square))
#define POP_BIT(board, square) (GET_BIT(board, square) ? board ^= (1ULL << square) : 0)

typedef unsigned long long u64;
// 3d array of shared pointers in shape of attack dictionary
typedef std::shared_ptr<std::shared_ptr<std::shared_ptr<u64[NUMBER_OF_SQUARES]>[NUMBER_OF_PIECES]>[SIDES]> AttackDictionary;

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

class BitBoard
{
public:
	BitBoard(std::string fen);
	BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], const AttackDictionary& attackPatterns, uint8_t flags, uint8_t enPassant);

	std::shared_ptr<BitBoard> move(int startSquare, int endSquare, int promotionPiece=NO_PROMOTION) const;
	std::shared_ptr<BitBoard> castleMove(bool isLong) const;
	std::string getFen() const;

	bool isCheck(bool color) const;

	void printBoard(bool isUnicode=false) const;

private:

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
	u64 m_pieces[SIDES][NUMBER_OF_PIECES];
	std::vector<std::pair<u64, u64>> m_whiteMoveList;
	std::vector<std::pair<u64, u64>> m_blackMoveList;
	u64 m_whiteAtkedSqrs;
	u64 m_blackAtkedSqrs;
	u64 m_whiteOccupancy;
	u64 m_blackOccupancy;

	std::shared_ptr<BitBoard> createNextPosition(u64 nextPos[SIDES][NUMBER_OF_PIECES], uint8_t nextFlags, uint8_t nextEnPassant) const;
	std::vector<std::pair<u64, u64>> getPseudoLegalMoves(bool color) const;
	bool isMovePseudoLegal(int startSquare, int endSquare) const;

	void parseFen(std::string fen);
	void initAtkDictionary();

	int getPieceType(int square, bool color) const;
	int getPieceType(u64 square, bool color) const;
	static int getLsbIndex(u64 board);
	static inline int bitCount(u64 board);
	
	u64 getSideOccupancy(const bool color) const; 
	u64 getAttackSqrs(const bool color) const;
	u64 getPromotionMask() const;

	u64 removeBishopBlockedAtk(int square, u64 atk, bool color) const;
	u64 removeRookBlockedAtk(int square, u64 atk, bool color) const;
	u64 removeQueenBlockedAtk(int square, u64 atk, bool color) const;
	u64 removePawnIllegalAtk(u64 atk, bool color) const;
	u64 getPawnMovementPattern(int square, bool color) const;
	u64 getEnPassantPattern(int square, bool color) const;
	
	void getPiecesCopy(u64 pieces[SIDES][NUMBER_OF_PIECES]) const;
	bool isCastlingPossible(bool isLongCastle) const;

	//====== Attack Patterns ======//
	static u64 calcWhitePawnAtkPattern(int square);
	static u64 calcBlackPawnAtkPattern(int square);
	static u64 calcKnightAtkPattern(int square);
	static u64 calcRookAtkPattern(int square);
	static u64 calcBishopAtkPattern(int square);
	static u64 calcKingAtkPattern(int square);
	static u64 calcQueenAtkPattern(int square);

};

#endif

