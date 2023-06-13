#pragma once
#include "IBoard.h"
#include <iostream>

#define NUMBER_OF_PIECES 6
#define NUMBER_OF_SQUARES 64
#define BLACK 0
#define WHITE 1
#define SIDES 2
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

#define GET_BIT(piece, square) ((piece & (1ULL << square)) ? 1 : 0)
#define SET_BIT(piece, square) (piece |= (1ULL << square))

typedef unsigned long long u64;

// squares
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

class BitBoard : public IBoard
{
public:
	BitBoard(u64 pieces[SIDES][NUMBER_OF_PIECES]);
	BitBoard();

	IBoard* move(std::string startPos, std::string endPos);
	std::string getFEN();

	void printBoard();
	void printBoardUnicode();
	void printPieceBitBoard(int color, int piece);


private:
	u64 m_pieces[SIDES][NUMBER_OF_PIECES];
	u64 m_attackPatterns[SIDES][NUMBER_OF_PIECES][NUMBER_OF_SQUARES];

	u64 getUnifiedBoard();
	
	u64 calcBlackPawnAtkPattern(int square);
	u64 calcWhitePawnAtkPattern(int square);

};

