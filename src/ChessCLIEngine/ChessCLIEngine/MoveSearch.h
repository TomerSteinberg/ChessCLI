#pragma once
#include <memory>
#include "BitBoard.h"
#include <string>
#include <unordered_map>

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define EQUAL 0

class MoveSearch
{
public:
	static std::unordered_map<u64, std::pair<double, int>> transpositionTable;
	static int minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth, int alpha=MIN_INFINITY, int beta=MAX_INFINITY);
};

