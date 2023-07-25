#pragma once
#include <iostream>
#include <memory>

#define NUMBER_OF_PIECES 6
#define NUMBER_OF_SQUARES 64
#define BLACK 0
#define WHITE 1
#define SIDES 2
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

#define GET_BIT(board, square) ((board & (1ULL << square)) ? 1 : 0)
#define SET_BIT(board, square) (board |= (1ULL << square))

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
	BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES]);
	BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES], AttackDictionary& attackPatterns, bool color);

	BitBoard* move(int startSquare, int endSquare);
	std::string getFEN();

	void printBoard();
	void printBoardUnicode();
	void printPieceBitBoard(int color, int piece);

private:
	const bool m_currColor;
	u64 m_pieces[SIDES][NUMBER_OF_PIECES];
	const AttackDictionary m_attackPatterns;

	
	u64 getOccupancy() const;
	u64 getWhiteOccupancy() const; 
	u64 getBlackOccupancy() const; 
	
	static inline int bitCount(u64 board);

	//====== Attack Patterns ======//
	static u64 calcWhitePawnAtkPattern(int square);
	static u64 calcBlackPawnAtkPattern(int square);
	static u64 calcKnightAtkPattern(int square);
	static u64 calcRookAtkPattern(int square);
	static u64 calcBishopAtkPattern(int square);
	static u64 calcKingAtkPattern(int square);
	static u64 calcQueenAtkPattern(int square);

};



