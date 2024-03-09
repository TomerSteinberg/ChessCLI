#pragma once
#include <memory>
#include "BitBoard.h"
#include <string>
#include <unordered_map>

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define EQUAL 0

#define TRANSPOTION_TABLE_SIZE 2000000

class MoveSearch
{
public:
	static int nodes;
	static int transpositionTable[TRANSPOTION_TABLE_SIZE];
	static int depthTable[TRANSPOTION_TABLE_SIZE];
	static int minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth, int alpha=MIN_INFINITY, int beta=MAX_INFINITY);
};

