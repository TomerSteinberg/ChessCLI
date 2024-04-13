#pragma once
#include <memory>
#include "BitBoard.h"
#include <string>
#include <unordered_map>
#include "Game.h"

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define EQUAL 0

#define TRANSPOTION_TABLE_SIZE 67108864

class MoveSearch
{
public:
	static int nodes;
	static std::pair<int, int> transpositionTable[TRANSPOTION_TABLE_SIZE];
	static int minimax(const std::shared_ptr<BitBoard> position, const bool isMaximizingPlayer, const unsigned int depth, int alpha=MIN_INFINITY, int beta=MAX_INFINITY);
	static int perft(std::shared_ptr<BitBoard> position, const unsigned int depth);
};

